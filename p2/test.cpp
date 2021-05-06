#include "tester/tester.h"

int main(int argc, char const *argv[]) {
    string testname = argv[1];
    
    if (testname == "all") {
        Tester::execute();
    } else if (testname == "singlePop") {
        Tester::testSinglePop(true);
    } else if (testname == "singlePush") {
        Tester::testSinglePush(true);
    } else if (testname == "correctItems") {
        Tester::testCorrectItems(true);
    } else if (testname == "multiplePop") {
        Tester::testPopStack(true);
    } else if (testname == "multiplePush") {
        Tester::testPushStack(true);
    }

    return 0;
}
