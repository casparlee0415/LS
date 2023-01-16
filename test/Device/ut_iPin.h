#include "../../src/Device/iPin.h"

class iPinTest : public ::testing::Test{
    protected:
        Device *device;

        void SetUp() override{
            device=new iPin(0);
            
        }
        void TearDown() override{
            delete device;
        }
};

TEST_F(iPinTest, getOutputTest) {
    ASSERT_EQ(0,device->getOutput());
}

TEST_F(iPinTest,setInputTest){
    dynamic_cast<iPin *>(device)->setInput(1);
    ASSERT_EQ(1,device->getOutput());
}

TEST_F(iPinTest, addInputPinTest){
    Device *device2=new iPin(0);
    ASSERT_ANY_THROW(device->addInputPin(device2));
    delete device2;
}

TEST_F(iPinTest,iPinEmptyTest){
    ASSERT_TRUE(device->iPinEmpty());
}