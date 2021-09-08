#include "Stat1DStudy.hpp"

// Constructors
Stat1DStudy::Stat1DStudy(HeplString filename, int column) {
    m_sample = nullptr;
    m_mode = nullptr;

    parseToSample(filename, column);

    computeStats();

    // Display report
    displayReport();

    if (m_sample->getDataSource()->getType() == 'C') {
        HeplString input;

        std::cout << "Please specify a start value : ";
        std::cin >> input;
        double start = atof(input.c_str());
        ((DataSourceSerieContinue*)m_sample->getDataSource())->setStart(start);

        std::cout << "Please specify an interval : ";
        std::cin >> input;
        double interval = atof(input.c_str());
        ((DataSourceSerieContinue*)m_sample->getDataSource())->setInterval(interval);

        m_startIntervalSet = true;

        HeplList<Data1D> itemOccurrenceList = ((DataSourceSerieContinue*)m_sample->getDataSource())->getItemOccurrenceList();
        HeplList<HeplList<double>> rangeOccurrenceList = getRangeOccurrenceList(itemOccurrenceList);
        ((DataSourceSerieContinue*)m_sample->getDataSource())->setRangeOccurrenceList(rangeOccurrenceList);

        // Display report
        displayReport();
    }
}

void Stat1DStudy::parseToSample(const HeplString& filename, int column) {

    // Ensure file is well formed
    HeplList<HeplBaseException> errors;
    errors = isFileMalformed(filename.c_str());
    if (errors.getNumberItems()) {
        for (size_t i = 0; i < errors.getNumberItems(); i++) {
            std::cout << ((HeplBaseException)errors[i]).what() << std::endl;
        }
        throw errors[0];
    }

    std::ifstream file(filename.c_str());

    // Parsing header of the file
    HeplString name;
    HeplString subject;
    HeplString type;
    file >> name;
    file >> subject;
    file >> type;

    // Check column
    if (column < 0) {
        std::cout << "[!] The specified column value cannot be below 0. Defaulting to column 0."
                  << std::endl;
        column = 0;
    } else if ((size_t) column >= type.explode(FILE_DELIMITER).getNumberItems()) {
        std::cout << "[!] The specified column value cannot be above the max number of columns of "
                  << type.explode(FILE_DELIMITER).getNumberItems()
                  << " - 1 (because counting from 0 in a table). Defaulting to column 0."
                  << std::endl;
        column = 0;
    }

    subject = subject.explode(FILE_DELIMITER)[column];
    type = type.explode(FILE_DELIMITER)[column];

    // Creating our sample
    m_sample = new Sample();

    // Creating our data source
    DataSource *source;
    if (type == 'D') {
        source = new DataSourceSerieDiscrete();
        source->setType('D');

    } else if (type == 'C') {
        source = new DataSourceSerieContinue();
        source->setType('C');

    } else {
        throw HeplBaseException("Study type invalid. Must be \"D\" or \"C\"");
    }

    m_sample->setDataSource(source);

    // Assigning data source details
    m_sample->getDataSource()->setName(name);
    m_sample->getDataSource()->setSubject(subject);

    // Sort read values to be able to count them more efficiently
    HeplSortedList<double> sortedList;
    HeplString line;
    while (file >> line) {
        HeplString explodedString = line.explode(FILE_DELIMITER)[column];
        // Prevent blank lines to be considered as 0
        if (!explodedString.empty()) {
            sortedList.add(atof(explodedString.c_str()));
        }
    }

    HeplList<Data1D> itemOccurrenceList = getItemOccurrenceList(sortedList);

    if (m_sample->getDataSource()->getType() == 'D') {
        ((DataSourceSerieDiscrete*)m_sample->getDataSource())->setItemOccurrenceList(itemOccurrenceList);
        ((DataSourceSerieDiscrete*)m_sample->getDataSource())->setSortedList(sortedList);
    } else {
        ((DataSourceSerieContinue*)m_sample->getDataSource())->setItemOccurrenceList(itemOccurrenceList);
        ((DataSourceSerieContinue*)m_sample->getDataSource())->setSortedList(sortedList);
    }
}

void Stat1DStudy::computeStats() {

    // Count total effective. Needs to be first, because we need this value for
    // other computations.
    m_sample->getDataSource()->setTotalHeadcount(getTotalHeadcount());

    // Compute range
    m_range = getRange();

    // Compute mean
    m_mean = getMean();

    // Compute median
    m_median = getMedian();

    // Compute mode
    m_mode = getMode();

    // Compute standard deviation
    m_sd = getStandardDeviation();

    // Compute variation coefficient
    m_variationCoefficient = getVariationCoefficient();

    // Compute min and max value
    m_dataControlMin = getMinValueFromSample();
    m_dataControlMax = getMaxValueFromSample();
}

// Others
void Stat1DStudy::displayReport() const {
    std::cout << "Name                  : "
        << m_sample->getDataSource()->getName() << std::endl;
    std::cout << "Subject of the study  : "
        << m_sample->getDataSource()->getSubject() << std::endl;
    std::cout << "Type                  : "
        << m_sample->getDataSource()->getType() << std::endl;

    // Display data
    displayRecords();
    std::cout << "----------------------- " << std::endl;

    // Display range
    std::cout << "Range                 : " << m_range << std::endl;

    // Display mean
    std::cout << "Mean                  : " << m_mean << std::endl;

    // Display median
    std::cout << "Median                : " << m_median << std::endl;

    // Display mode
    std::cout << "Mode                  : " << m_mode[0] << " : " << m_mode[1] << " : " << m_mode[2] << std::endl;

    // Display standard deviation
    std::cout << "Standard deviation    : " << m_sd << " (rounded: " << std::ceil(m_sd * 100.0) / 100.0 << ")" << std::endl;

    // Compute variation coefficient
    std::cout << "Variation coefficient : " << m_variationCoefficient << " (" << m_variationCoefficient * 100 << " %)" << std::endl;

    // Display headcount
    std::cout << "Total headcount       : " << getTotalHeadcount() << std::endl;

    std::cout << "----------------------- " << std::endl;
    std::cout << "Quality control         " << std::endl;
    std::cout << "* Min value           : " << m_dataControlMin << std::endl;
    std::cout << "* Max value           : " << m_dataControlMax << std::endl;
}

void Stat1DStudy::displayRecords() const {

    std::cout << "Data                  : ";

    if (m_sample->getDataSource()->getType() == 'D') {
        HeplList<Data1D> list = ((DataSourceSerieDiscrete*)m_sample->getDataSource())->getItemOccurrenceList();
        Data1D data;
        for (size_t i = 0; i < list.getNumberItems(); i++) {
            data = list[i];
            std::cout << "(" << data.getValue() << ", " << data.getHeadcount() << ") ";
        }
        // QApplication *qtApp;
        // GraphStat1DDiscrete w(*this);
        // w.show();
        // qtApp->exec();

    } else {

        // When the program is first run, we need to display the records we
        // have in the file, that way, the operator can choose the start and
        // interval limit he wants.
        if (!m_startIntervalSet) {
            HeplList<Data1D> list = ((DataSourceSerieContinue*)m_sample->getDataSource())->getItemOccurrenceList();
            Data1D data;
            for (size_t i = 0; i < list.getNumberItems(); i++) {
                data = list[i];
                std::cout << "(" << data.getValue() << ", " << data.getHeadcount() << ") ";
            }

        } else {

            // Get the max number of digits required, will be used for the view
            // below with setw
            size_t maxNumberDigits = HeplString(getMaxValueFromSample()).size();
            HeplList<HeplList<double>> list = ((DataSourceSerieContinue*)m_sample->getDataSource())->getRangeOccurrenceList();

            for (size_t i = 0;i < list.getNumberItems(); i++) {

                // We don't want a space for the first line
                HeplString space = (i == 0) ? "" : "                        ";

                std::cout << space
                          << "[ "
                          << std::setw(maxNumberDigits) << list[i][0]
                          << ", "
                          << std::setw(maxNumberDigits) << list[i][1]
                          << " [ : "
                          << list[i][2]
                          << std::endl;
            }
        }
    }

    std::cout << std::endl;
}

HeplList<HeplBaseException> Stat1DStudy::isFileMalformed(const HeplString& filename) const {
    HeplList<HeplBaseException> errors;

    std::ifstream file(filename.c_str());
    if (!file) {
        errors.add(HeplBaseException("Unable to open the file " + filename));
        return errors;
    }

    HeplString name;
    file >> name;
    if (name.empty()) {
        errors.add(HeplBaseException("Study name missing"));
    }

    HeplString subject;
    file >> subject;
    size_t numberOfSubjects = 0;
    if (subject.empty()) {
        errors.add(HeplBaseException("Study subject missing"));
    } else {
        numberOfSubjects = subject.explode(FILE_DELIMITER).getNumberItems();
    }

    HeplString type;
    file >> type;
    size_t numberOfTypes = 0;
    if (type.empty()) {
        errors.add(HeplBaseException("Study type missing"));
        return errors;
    } else {
        numberOfTypes = type.explode(FILE_DELIMITER).getNumberItems();
    }

    if (numberOfSubjects != numberOfTypes) {
        errors.add(HeplBaseException("Number of subjects and number of types differs"));
        return errors;
    }

    HeplString line;
    size_t numberOfFields = 0;
    for (size_t i = 4; file >> line; i++) {
        numberOfFields = line.explode(FILE_DELIMITER).getNumberItems();
        if (numberOfFields != numberOfTypes) {
            errors.add(
                HeplBaseException("Line "
                    + HeplString(i)
                    + " has "
                    + HeplString(numberOfFields)
                    + " fields instead of "
                    + HeplString(numberOfTypes)
                )
            );

        }
    }

    return errors;
}

HeplList<Data1D> Stat1DStudy::getItemOccurrenceList(const HeplSortedList<double>& sortedList) {

    // Count number of occurrences for each element in the list, like a group
    // by statement in RDBMS which creates records like this:
    // (item_x, amount), (item_y, amount), (item_z, amount),...
    HeplList<Data1D> itemOccurrenceList;
    double prevValue = 0;
    unsigned int amount = 0;
    Data1D toAdd;
    bool changeDetected = false;
    for (size_t i = 0; i < sortedList.getNumberItems() + 1; i++) {

        // If the current value is different from the previous one, we can stop
        // counting. Using that same logic, we need to get out of bounds
        // explaining the catch requirement.
        try {
            changeDetected = (sortedList[i] != prevValue && i != 0) ? true : false;
        } catch (const HeplBaseListItemNotFoundException& e) {
            changeDetected = true;
        }

        if (changeDetected) {
            toAdd.setValue(prevValue);
            toAdd.setHeadcount(amount);
            itemOccurrenceList.add(toAdd);
            amount = 0;

            // We are out of bound, so that's OK, we are at the end.
            if (i >= sortedList.getNumberItems()) {
                break;
            }
        }

        prevValue = sortedList[i];
        amount++;
    }
    return itemOccurrenceList;
}

HeplList<HeplList<double>> Stat1DStudy::getRangeOccurrenceList(const HeplList<Data1D>& itemOccurrenceList) {

    HeplList<HeplList<double>> list;

    // Accessing the model
    double start = ((DataSourceSerieContinue*)m_sample->getDataSource())->getStart();
    double interval = ((DataSourceSerieContinue*)m_sample->getDataSource())->getInterval();

    double value = ((Data1D)itemOccurrenceList[0]).getValue();
    unsigned int headcount = 0;
    unsigned int rangeHeadcount = 0;
    size_t i = 0;
    while (i < itemOccurrenceList.getNumberItems()) {

        while (value < start + interval) {
            headcount = ((Data1D)itemOccurrenceList[i]).getHeadcount();
            rangeHeadcount += headcount;
            i++;
            if (i == itemOccurrenceList.getNumberItems()) {
                break;
            }
            value = ((Data1D)itemOccurrenceList[i]).getValue();
        }
        HeplList<double> listItem;
        listItem.add(start);
        listItem.add(start + interval);
        listItem.add(rangeHeadcount);
        list.add(listItem);
        start += interval;
        rangeHeadcount = 0;
    }

    return list;
}

Sample* Stat1DStudy::getSample() const {
    return m_sample;
}

unsigned int Stat1DStudy::getTotalHeadcount() const {
    HeplList<Data1D> list;
    if (m_sample->getDataSource()->getType() == 'D') {
        list = ((DataSourceSerieDiscrete*)m_sample->getDataSource())->getItemOccurrenceList();
    } else {
        list = ((DataSourceSerieContinue*)m_sample->getDataSource())->getItemOccurrenceList();
    }

    unsigned int eff = 0;
    for (size_t i = 0; i < list.getNumberItems(); i++) {
        eff += ((Data1D&)list[i]).getHeadcount();
    }
    return eff;
}

double Stat1DStudy::getRange() const {
    const HeplList<Data1D>& list = ((DataSourceSerieDiscrete*)m_sample->getDataSource())->getItemOccurrenceList();
    double min = ((Data1D&)list[0]).getValue();
    double max = ((Data1D&)list[list.getNumberItems() - 1]).getValue();

    return max - min;
}

double Stat1DStudy::getMean() const {

    HeplList<Data1D> list;
    if (m_sample->getDataSource()->getType() == 'D') {
        list = ((DataSourceSerieDiscrete*)m_sample->getDataSource())->getItemOccurrenceList();
    } else {
        list = ((DataSourceSerieContinue*)m_sample->getDataSource())->getItemOccurrenceList();
    }

    double sumXi = 0;
    for (size_t i = 0; i < list.getNumberItems(); i++) {
        sumXi += ((Data1D &)list[i]).getValue() * ((Data1D &)list[i]).getHeadcount();
    }

    unsigned int n = m_sample->getDataSource()->getTotalHeadcount();

    return sumXi / n;
}

double Stat1DStudy::getMedian() const {

    const HeplSortedList<double> *sortedValuesList;
    if (m_sample->getDataSource()->getType() == 'D') {
        sortedValuesList = &((DataSourceSerieDiscrete*)m_sample->getDataSource())->getSortedList();
    } else {
        sortedValuesList = &((DataSourceSerieContinue*)m_sample->getDataSource())->getSortedList();
    }

    double median;

    if (sortedValuesList->getNumberItems() % 2) {

        // When odd:
        // 1, 3, 3, **6**, 7, 8, 9
        //
        // Yes, the logic is inverted since arrays start à 0, we used floor.
        median = (*sortedValuesList)[std::floor(sortedValuesList->getNumberItems() / 2)];

    } else {
        // When even:
        // 1, 2, 3, **4, 5**, 6, 8, 9
        // Linear interpolation: (4 + 5) / 2 ==> 4.5
        double medianLimit1 = (*sortedValuesList)[sortedValuesList->getNumberItems() / 2 - 1];
        double medianLimit2 = (*sortedValuesList)[sortedValuesList->getNumberItems() / 2];
        median = (medianLimit1 + medianLimit2) / 2;
    }

    return median;
}

double *Stat1DStudy::getMode() const {

    const HeplList<Data1D> *list;
    if (m_sample->getDataSource()->getType() == 'D') {
        list = &((DataSourceSerieDiscrete*)m_sample->getDataSource())->getItemOccurrenceList();
    } else {
        list = &((DataSourceSerieContinue*)m_sample->getDataSource())->getItemOccurrenceList();
    }

    // We are only reporting the max. 3 modes, in practice, this can be
    // multimodal with (theoretically) no limit.
    const unsigned int MAX_MODES = 3;
    double *mode = new double[MAX_MODES]{0};
    unsigned int modeEffectif = 0;

    for (size_t i = 0; i < list->getNumberItems(); i++) {
        unsigned int eff = ((Data1D&)(*list)[i]).getHeadcount();
        if (eff > modeEffectif) {
            modeEffectif = eff;
        }
    }

    for (size_t i = 0, j = 0; i < list->getNumberItems(); i++) {
        unsigned int eff = ((Data1D&)(*list)[i]).getHeadcount();
        if (eff == modeEffectif) {
            double value = ((Data1D&)(*list)[i]).getValue();
            mode[j]  = value;
            j++;
            // We are only keeping 3 modes. Avoid out of bounds.
            if (j == MAX_MODES) {
                break;
            }
        }
    }

    return mode;
}

double Stat1DStudy::getStandardDeviation() const {

    const HeplList<Data1D> *list;
    if (m_sample->getDataSource()->getType() == 'D') {
        list = &((DataSourceSerieDiscrete*)m_sample->getDataSource())->getItemOccurrenceList();
    } else {
        list = &((DataSourceSerieContinue*)m_sample->getDataSource())->getItemOccurrenceList();
    }

    unsigned int n = m_sample->getDataSource()->getTotalHeadcount();

    double nixi1 = 0;
    for (size_t i = 0; i < list->getNumberItems(); i++) {
        unsigned int ni = (*list)[i].getHeadcount();
        double xi = (*list)[i].getValue();
        nixi1 += ni * pow(xi, 2);
    }

    double nixi2 = 0;
    for (size_t i = 0; i < list->getNumberItems(); i++) {
        unsigned int ni = (*list)[i].getHeadcount();
        double xi = (*list)[i].getValue();
        nixi2 += ni * xi;
    }
    nixi2 = pow(nixi2, 2);

    return sqrt((nixi1 - nixi2 / n) / n);
}

double Stat1DStudy::getVariationCoefficient() const {
    return m_sd / m_mean;
}

double Stat1DStudy::getMinValueFromSample() const {
    HeplList<Data1D> list = ((DataSourceSerieDiscrete*)m_sample->getDataSource())->getItemOccurrenceList();
    return ((Data1D&)list[0]).getValue();
}

double Stat1DStudy::getMaxValueFromSample() const {
    HeplList<Data1D> list = ((DataSourceSerieDiscrete*)m_sample->getDataSource())->getItemOccurrenceList();
    return ((Data1D&)list[list.getNumberItems() - 1]).getValue();
}

// Destructor
Stat1DStudy::~Stat1DStudy() {
    if (m_sample != nullptr) {
        delete this->m_sample;
    }
    if (m_mode != nullptr) {
        delete[] m_mode;
    }
}
