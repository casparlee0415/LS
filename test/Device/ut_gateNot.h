#include "../../src/Device/gateNot.h"
#include "../../src/Device/iPin.h"

class gateNotTest : public ::testing::Test{
    protected:
        Device *device1,*device2,*device3;

        void SetUp() override{
            device1=new gateNot();
            device2=new iPin(1);
            device3=new iPin(0);
        }
        void TearDown() override{
            delete device1;
            delete device2;
            delete device3;
        }
};

TEST_F(gateNotTest, getOutputTest) {
    device1->addInputPin(device2);

    ASSERT_EQ(0,device1->getOutput());
}

TEST_F(gateNotTest, addInputPinTest){
    device1->addInputPin(device2);
    
    ASSERT_ANY_THROW(device1->addInputPin(device3));
}

TEST_F(gateNotTest,iPinEmptyTest){
    ASSERT_TRUE(device1->iPinEmpty());
}
