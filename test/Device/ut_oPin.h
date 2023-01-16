#include "../../src/Device/iPin.h"
#include "../../src/Device/oPin.h"

class oPinTest : public ::testing::Test{
    protected:
        Device *device1,*device2;

        void SetUp() override{
            device1=new iPin(0);
            device2=new oPin();
        }
        void TearDown() override{
            delete device1;
            delete device2;
        }
};

TEST_F(oPinTest, getOutputTest) {
    device2->addInputPin(device1);
    ASSERT_EQ(0,device2->getOutput());
}

TEST_F(oPinTest, addInputPinTest){
    Device *device3=new iPin(1);

    device2->addInputPin(device1);
    ASSERT_ANY_THROW(device2->addInputPin(device3));
    delete device3;
}

TEST_F(oPinTest,iPinEmptyTest){
    ASSERT_TRUE(device2->iPinEmpty());
}