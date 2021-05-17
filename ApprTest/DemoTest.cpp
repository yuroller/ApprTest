// Boilerplate per utilizzare ApprovalTests.cpp
#define APPROVAL_TESTS_HIDE_DEPRECATED_CODE 1

#include "ApprovalTests.hpp"
#include "catch2/catch.hpp"

// Include per i nostri test e le nostre classi
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

// Scriviamo meno e il test è più chiaro
using namespace ApprovalTests;

// La nostra classe da testare
class DeepTought
{
public:
    DeepTought(int a, int b)
        : a_(a), b_(b) {}
    int a() const { return a_; }
    int b() const { return b_; }

    int getAnswer() const { return a_ * b_; }
    
    std::string getIdentity() const {
        std::stringstream ss;
        ss << "[DeepTought 0x"
            << std::hex << std::setw(8) << std::setfill('0')
            << this
            << " (a,b)=(" << a_ << "," << b_ << ")]";
        return ss.str();
    }

private:
    int a_;
    int b_;
};


// Test semplice, ma di scarso utilizzo pratico
// meglio usare classico unit test con assert
TEST_CASE("DeepToughtAnswerFor6And7")
{
    // Arrange
    auto computer = DeepTought(6, 7);

    // Act
    auto answer = computer.getAnswer();

    // Print 'actual' value
    auto received = std::to_string(answer);

    // Compare received with approved ('expected') text
    Approvals::verify(received);
}

// Test di istanze multiple (più utile)
//TEST_CASE("DeepToughtAnswerForMultipleInput")
//{
//    std::vector<std::pair<int, int>> computers{ {6, 7}, {5, 4}, {2, 10} };
//
//    Approvals::verifyAll(
//        "computers",
//        computers,
//        [](std::pair<int, int> arg, std::ostream& os){
//            auto c = DeepTought(arg.first, arg.second);
//            os << "(" << c.a() << "," << c.b() << ") => " << c.getAnswer();
//        }
//    );
//}

// Quando non vogliamo/possiamo modificare classe da testare,
// ma vogliamo renderla 'stampabile' facilmente

// wrapper, ma va bene anche ereditarietà
class PrintableDeepTought {
public:
    explicit PrintableDeepTought(const DeepTought& computer)
        : _computer(computer) {}

    friend std::ostream& operator<<(std::ostream& os,
        const PrintableDeepTought& wrapper) {
        return os << "(" << wrapper._computer.a() << "," << wrapper._computer.b() << ")";
    }

private:
    const DeepTought& _computer;
};

// Stesso test di prima ma più leggibile
//TEST_CASE("DeepToughtAnswerForMultipleInputWithPrinter")
//{
//    std::vector<DeepTought> computers{ {6, 7}, {5, 4}, {2, 10} };
//
//    Approvals::verifyAll(
//        "computers",
//        computers,
//        [](DeepTought c, std::ostream& os) {
//            os << PrintableDeepTought(c) << " => " << c.getAnswer();
//        }
//    );
//}

// Voglio provare il 'prodotto cartesiano' di più input
//TEST_CASE("DeepToughtAnswerForCombinatorialInput")
//{
//    std::vector<int> paramA{ 2, 4, 6 };
//    std::vector<int> paramB{ 1, 3, 5, 7, 9 };
//
//    CombinationApprovals::verifyAllCombinations(
//        [](int a, int b) {
//            auto computer = DeepTought(a, b);
//            return computer.getAnswer();
//        },
//        paramA,
//        paramB);
//}

// A volte occorre filtrare dati non interessanti
//TEST_CASE("DeepToughtIdentity")
//{
//    auto computer = DeepTought(21, 2);
//
//    Approvals::verify(computer.getIdentity(),
//        Options(Scrubbers::createRegexScrubber(R"(0x[0-9A-F]+)", "{id}")));
//}

