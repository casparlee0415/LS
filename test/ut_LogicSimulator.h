#include "../src/LogicSimulator.h"

class LogicSimulatorTest : public ::testing::Test{
    protected:
        LogicSimulator LS=LogicSimulator::getInstance();
        std::string filename;

        void SetUp() override{
            filename="File1.lcf";
        }

        void TearDown() override{}
};

TEST_F(LogicSimulatorTest, loadTest) {
    
    ASSERT_TRUE(LS.load(filename));
}

TEST_F(LogicSimulatorTest, getSimulationResultTest){
    std::vector<int> input={1,0,1};
    std::string result=std::string("Simulation Result:\ni i i | o\n1 2 3 | 1\n------+--\n1 0 1 | 1\n");

    LS.load(filename);
    ASSERT_EQ(result,LS.getSimulationResult(input));
}

TEST_F(LogicSimulatorTest, getTruthTableTest){
    std::string result("Truth table:\ni i i | o\n1 2 3 | 1\n------+--\n0 0 0 | 0\n0 0 1 | 0\n0 1 0 | 0\n0 1 1 | 0\n1 0 0 | 1\n1 0 1 | 1\n1 1 0 | 0\n1 1 1 | 0\n");

    LS.load(filename);
    ASSERT_EQ(result,LS.getTruthTable());
}
