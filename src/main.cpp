#include "main.hpp"

using namespace std;

int main(int argc, char* argv[]) {

    qtApp = new QApplication(argc, argv);

    try {

        if (argc == 2) {
            HeplString filename(argv[1]);
            Stat1DStudy E(filename, 0);

        } else if (argc == 3) {
            HeplString filename(argv[1]);
            HeplString column(argv[2]);
            Stat1DStudy E(filename, column.atoi());

        } else if (argc == 4) {

        } else {
            throw HeplBaseException("Invalid number of arguments");
        }

    } catch (HeplBaseException e) {
        cout << e.what() << endl;
        cout << "Example: $ " << argv[0] << " data.dat" << endl;
    }
}
