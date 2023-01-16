#include "../../src/Device/gateOR.h"
#include "../../src/Device/iPin.h"

class gateORTest : public ::testing::Test{
    protected:
        Device *device1,*device2,*device3,*device4;

        void SetUp() override{
            device1=new gateOR();
            device2=new iPin(0);
            device3=new iPin(1);
            device4=new iPin(0);  
        }
        void TearDown() override{
            delete device1;
            delete device2;
            delete device3;
            delete device4;
        }
};

TEST_F(gateORTest, getOutputTest) {
    device1->addInputPin(device2);
    device1->addInputPin(device3);

    ASSERT_EQ(1,device1->getOutput());
}

TEST_F(gateORTest, addInputPinTest){
    device1->addInputPin(device2);
    device1->addInputPin(device4);

    ASSERT_EQ(0,device1->getOutput());
}

TEST_F(gateORTest,iPinEmptyTest){
    ASSERT_TRUE(device1->iPinEmpty());
}
