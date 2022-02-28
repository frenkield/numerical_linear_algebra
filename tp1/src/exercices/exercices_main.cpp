#define CATCH_CONFIG_RUNNER
#include <iostream>
#include <outils/catch.hpp>

using namespace std;

int main(int argc, char* argv[]) {

    if (argc < 2) {
        cout << "Usage:" << endl;
        cout << "    bin/exercices -l // afficher les noms des exercices" << endl;
        cout << "    bin/exercices [nom] // executer un test - il faut les crochets" << endl;

    } else {
        return Catch::Session().run(argc, argv);
    }
}
