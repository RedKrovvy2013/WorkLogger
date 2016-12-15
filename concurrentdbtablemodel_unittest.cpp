#include "concurrentdbtablemodel.h"
#include "fakedbtalkerfriend.h"
#include "gtest/gtest.h"

#include <QString>

class ConcurrentDBTableModelTest : public testing::Test {
public:
	ConcurrentDBTableModelTest() : tablemodel1(new FakeDBTalkerFriend()) {}
protected:
	ConcurrentDBTableModel tablemodel1;
};

TEST_F(ConcurrentDBTableModelTest, setTable) {
	tablemodel1.setTable("bar");
	ASSERT_STREQ("bar", tablemodel1.getTablename().toLocal8Bit().constData());
}

int main(int argc, const char * argv[]) {

    testing::InitGoogleTest(&argc, (char**)argv);
    RUN_ALL_TESTS();
}