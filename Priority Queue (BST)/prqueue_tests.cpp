/*-------------------------------------------
 Project 4 - Priority Queue (BST)
 Have created a templated binary search tree
 Designed a particular implementation of a priority queue
 Implemented multiple traversals through a binary search tree
 
System: xcode
------------------------------------------- */


#include "prqueue.h"
#include "gtest/gtest.h"

using namespace std;

// Test for default constructor and size
TEST(PrQueueTest, DefaultConstructorAndSize) {
    prqueue<int> pq;
    EXPECT_EQ(0, pq.size());
}

// Test for enqueue and peek with same priority elements
TEST(PrQueueTest, EnqueueAndPeekWithSamePriority) {
    prqueue<string> pq;
    pq.enqueue("first", 1);
    pq.enqueue("second", 2);
    pq.enqueue("second_same_priority", 2);
    pq.dequeue();
    EXPECT_EQ("second", pq.peek());
    EXPECT_EQ(2, pq.size());
}


// Test for clear
TEST(PrQueueTest, Clear) {
    prqueue<double> pq;
    pq.enqueue(1.1, 1);
    pq.enqueue(2.2, 2);
    pq.clear();
    EXPECT_EQ(0, pq.size());
    EXPECT_EQ(double{}, pq.peek());
}

// Test for as_string with same priority elements
TEST(PrQueueTest, AsStringWithSamePriority) {
    prqueue<int> pq;
    pq.enqueue(10, 2);
    pq.enqueue(20, 1);
    pq.enqueue(30, 3);
    pq.enqueue(25, 1);
    string expected = "1 value: 20\n1 value: 25\n2 value: 10\n3 value: 30\n";
    EXPECT_EQ(expected, pq.as_string());
}

// Test for copy constructor
TEST(PrQueueTest, CopyConstructor) {
    prqueue<int> pq1;
    pq1.enqueue(10, 2);
    pq1.enqueue(20, 1);
    prqueue<int> pq2(pq1);
    EXPECT_EQ(pq1.as_string(), pq2.as_string());
}

// Test for assignment operator
TEST(PrQueueTest, AssignmentOperator) {
    prqueue<int> pq1;
    pq1.enqueue(10, 2);
    pq1.enqueue(20, 1);
    prqueue<int> pq2;
    pq2 = pq1;
    pq2 = pq2;
    EXPECT_EQ(pq1.as_string(), pq2.as_string());
    
}


// Test for assignment operator

TEST(PrQueueTest, AssignmentOperator2) {
    prqueue<int> pq1;
    pq1.enqueue(10, 2);
    pq1.enqueue(20, 1);
    prqueue<int> pq2;
    pq2 = pq1;
    pq2 = pq2;
    EXPECT_EQ(pq1.as_string(), pq2.as_string());
    pq2.dequeue();
    EXPECT_FALSE(pq1.peek() == pq2.peek());
    
    
}



TEST(PrQueueTest, AssignmentOperatorEmptyTree) {
    prqueue<int> pq;
    prqueue<int> pqAssign;
    pqAssign = pq;

    EXPECT_EQ(pq.size(), pqAssign.size());
    EXPECT_EQ(pq.as_string(), pqAssign.as_string());
}

TEST(PrQueueTest, CopyConstructorDuplicatePriorities) {
    prqueue<string> pq;
    pq.enqueue("A", 1);
    pq.enqueue("B", 1);
    pq.enqueue("C", 2);

    prqueue<string> pqCopy(pq);

    vector<string> expectedOrder = {"A", "B", "C"};
    pqCopy.begin();

    string value;
    int priority;
    size_t index = 0;
    while (pqCopy.next(value, priority)) {
         EXPECT_EQ(expectedOrder[index++], value);
    }
    EXPECT_EQ(index, expectedOrder.size());
}


TEST(PrQueueTest, AssignmentOperatorLargerToSmaller) {
    prqueue<int> pqSmall;
    pqSmall.enqueue(1, 1);
    pqSmall.enqueue(2, 2);

    prqueue<int> pqLarge;
    pqLarge.enqueue(3, 3);
    pqLarge.enqueue(4, 4);
    pqLarge.enqueue(5, 5);
    pqLarge.enqueue(6, 6);

    pqSmall = pqLarge;

    vector<int> expectedOrder = {3, 4, 5, 6};
    pqSmall.begin();

    int value;
    int priority;
    size_t index = 0;
    while (pqSmall.next(value, priority)) {
         EXPECT_EQ(expectedOrder[index++], value);
    }
    EXPECT_EQ(index, expectedOrder.size());
}




// Test for equivalence operator
TEST(PrQueueTest, EquivalenceOperator) {
    prqueue<int> pq1;
    pq1.enqueue(10, 2);
    pq1.enqueue(20, 1);
    prqueue<int> pq2;
    pq2.enqueue(10, 2);
    pq2.enqueue(20, 1);
    EXPECT_TRUE(pq1 == pq2);
    
    
    prqueue<string> a;
    a.enqueue("2", 2);
    a.enqueue("1", 1);
    a.enqueue("3", 3);
   
    prqueue<string> b;
    b.enqueue("2", 2);
    b.enqueue("3", 3);
    b.enqueue("1", 1);

    prqueue<string> c;
    c.enqueue("1", 1);
    c.enqueue("2", 2);
    c.enqueue("3", 3);
   
    EXPECT_TRUE(b == a) ;
    EXPECT_TRUE(!(b == c));

   a.clear();
   b.clear();
   c.clear();
    
    
    
}




TEST(PrQueueTest, biginnext) {
    prqueue<string> pq;
    prqueue<string> p;
    pq.enqueue("0    1",0);
    pq.enqueue("-3   1",-3);
    pq.enqueue("-4   1",-4);
    pq.enqueue("-2   1",-2);
    pq.enqueue("-1   1",-1);
    pq.enqueue("3    1",3);
    pq.enqueue("0    2",0);
    pq.enqueue("-3   2",-3);
    pq.enqueue("-4   2",-4);
    pq.enqueue("-2   2",-2);
    pq.enqueue("-1   2",-1);
    pq.enqueue("3    2",3);
    pq.enqueue("0    3",0);
    pq.enqueue("-3   3",-3);
    pq.enqueue("-4   3",-4);
    pq.enqueue("-2   3",-2);
    pq.enqueue("-1   3",-1);
    pq.enqueue("3    3",3);
    
    
    p = pq;
    
    pq.begin();
    
    
    
    string value;
    int priority;
    while (pq.next(value, priority)) {
        EXPECT_EQ(p.dequeue(), value );
    }
    
    
    
};


TEST(PrQueueTest, BeginAndNext2) {
    prqueue<string> pq;
    pq.enqueue("0_1", 0);
    pq.enqueue("-3_1", -3);
    pq.enqueue("-4_1", -4);
    pq.enqueue("-2_1", -2);
    pq.enqueue("-1_1", -1);
    pq.enqueue("3_1", 3);
    pq.enqueue("0_2", 0);
    pq.enqueue("-3_2", -3);
    pq.enqueue("-4_2", -4);
    pq.enqueue("-2_2", -2);
    pq.enqueue("-1_2", -1);
    pq.enqueue("3_2", 3);
    pq.enqueue("0_3", 0);
    pq.enqueue("-3_3", -3);
    pq.enqueue("-4_3", -4);
    pq.enqueue("-2_3", -2);
    pq.enqueue("-1_3", -1);
    pq.enqueue("3_3", 3);

    vector<string> expectedOrder = {
        "-4_1", "-4_2", "-4_3", "-3_1", "-3_2", "-3_3", "-2_1", "-2_2", "-2_3", "-1_1", "-1_2", "-1_3",
        "0_1", "0_2", "0_3", "3_1", "3_2", "3_3"
    };

    pq.begin();

    string value;
    int priority;
    size_t index = 0;
    while (pq.next(value, priority)) {
        EXPECT_EQ(expectedOrder[index++], value);
    }
    EXPECT_EQ(index, expectedOrder.size());
}


TEST(PrQueueTest, BeginAndNextEmpty) {
    prqueue<string> pq;

    pq.begin();

    string value;
    int priority;
    EXPECT_FALSE(pq.next(value, priority));
}



TEST(PrQueueTest, NextWithOnlyR) {
    prqueue<string> pq;
    pq.enqueue("root", 1);
    pq.enqueue("right1", 2);
    pq.enqueue("right2", 3);
    pq.enqueue("right3", 4);

    vector<string> expectedOrder = {"root", "right1", "right2", "right3"};

    pq.begin();

    string value;
    int priority;
    size_t index = 0;
    while (pq.next(value, priority)) {
        
        EXPECT_EQ(expectedOrder[index++], value);
        EXPECT_EQ(index,priority );
        
    }
    EXPECT_EQ(index, expectedOrder.size());
}





TEST(PrQueueTest, NextWithOnlyL) {
    prqueue<string> pq;
    pq.enqueue("root", 4);
    pq.enqueue("right1", 3);
    pq.enqueue("right2", 2);
    pq.enqueue("right3", 1);

    vector<string> expectedOrder = {"right3", "right2", "right1", "root"};

    pq.begin();

    string value;
    int priority;
    size_t index = 0;
    while (pq.next(value, priority)) {
        
        EXPECT_EQ(expectedOrder[index++], value);
        EXPECT_EQ(index,priority );
        
    }
    EXPECT_EQ(index, expectedOrder.size());
}

TEST(PrQueueTest, BeginAndNextBalancedTree) {
    prqueue<int> pq;
    pq.enqueue(4, 4);
    pq.enqueue(2, 2);
    pq.enqueue(6, 6);
    pq.enqueue(1, 1);
    pq.enqueue(3, 3);
    pq.enqueue(5, 5);
    pq.enqueue(7, 7);

    vector<int> expectedOrder = {1, 2, 3, 4, 5, 6, 7};

    pq.begin();

    int value;
    int priority;
    size_t index = 0;
    while (pq.next(value, priority)) {
        EXPECT_EQ(expectedOrder[index++], value);
    }
    EXPECT_EQ(index, expectedOrder.size());
}


TEST(PrQueueTest, BeginAndNextSingleElement) {
    prqueue<string> pq;
    pq.enqueue("only", 1);

    pq.begin();

    string value;
    int priority;
    EXPECT_TRUE(pq.next(value, priority));
    EXPECT_EQ("only", value);

    EXPECT_FALSE(pq.next(value, priority));
}


TEST(PrQueueTest, BeginAndNextTree) {
    prqueue<char> pq;
    pq.enqueue('F', 6);
    pq.enqueue('B', 2);
    pq.enqueue('G', 7);
    pq.enqueue('A', 1);
    pq.enqueue('D', 4);
    pq.enqueue('I', 9);
    pq.enqueue('C', 3);
    pq.enqueue('E', 5);
    pq.enqueue('H', 8);

    vector<char> expectedOrder = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};

    pq.begin();

    char value;
    int priority;
    size_t index = 0;
    while (pq.next(value, priority)) {
         EXPECT_EQ(expectedOrder[index++], value);
    }
    EXPECT_EQ(index, expectedOrder.size());
}




//
//
//
////template <typename T>
//
//#include "prqueue.h"
//
//int main() {
//    prqueue<string> pq;
//    prqueue<string> p;
//    
//    pq.enqueue("0    1",0);
//    pq.enqueue("-3   1",-3);
//    pq.enqueue("-4   1",-4);
//    pq.enqueue("-2   1",-2);
//    pq.enqueue("-1   1",-1);
//    pq.enqueue("3    1",3);
//    pq.enqueue("0    2",0);
//    pq.enqueue("-3   2",-3);
//    pq.enqueue("-4   2",-4);
//    pq.enqueue("-2   2",-2);
//    pq.enqueue("-1   2",-1);
//    pq.enqueue("3    2",3);
//    pq.enqueue("0    3",0);
//    pq.enqueue("-3   3",-3);
//    pq.enqueue("-4   3",-4);
//    pq.enqueue("-2   3",-2);
//    pq.enqueue("-1   3",-1);
//    pq.enqueue("3    3",3);
//    
//    cout << "Queue:\n" << pq.as_string() << endl<< endl;
//    
//    pq.begin();
//    string value;
//    int priority;
//    while (pq.next(value, priority)) {
//       cout << priority << " value: " << value << endl;
//     }
//    
//    pq.dequeue();
//    pq.dequeue();
//    pq.dequeue();
//    pq.dequeue();
//    pq.dequeue();
//    pq.dequeue();
//    pq.dequeue();
//    pq.dequeue();
//    pq.dequeue();
//    
//    cout << "Queue:\n" << pq.as_string() << endl;
//    
//    pq.begin();
////    string value;
////    int priority;
//    while (pq.next(value, priority)) {
//       cout << priority << " value: " << value << endl;
//     }
//    
//    
//    pq.enqueue("Gwen", 4);
//    pq.enqueue("Jen", 2);
//    pq.enqueue("Ben", 1);
//    pq.enqueue("Sven", 2);
//    pq.enqueue("malik", 3);
//    pq.enqueue("ma", 5);
//    pq.enqueue("man", 5);
//    pq.enqueue("manav", 6);
//    
//    
//    cout << "Peek: " << pq.peek() << endl;
//    cout << "Dequeue: " << pq.dequeue() << endl;
//    cout << "Size: " << pq.size() << endl;
//    
//    cout << "Peek: " << pq.peek() << endl;
//    cout << "Dequeue: " << pq.dequeue() << endl;
//    cout << "Size: " << pq.size() << endl;
//    
//    cout << "Peek: " << pq.peek() << endl;
//    cout << "Dequeue: " << pq.dequeue() << endl;
//    cout << "Size: " << pq.size() << endl;
//    
//    cout << "Peek: " << pq.peek() << endl;
//    cout << "Dequeue: " << pq.dequeue() << endl;
//    cout << "Size: " << pq.size() << endl;
//    
//    cout << "Peek: " << pq.peek() << endl;
//    cout << "Dequeue: " << pq.dequeue() << endl;
//    cout << "Size: " << pq.size() << endl;
//    
//    cout << "Peek: " << pq.peek() << endl;
//    cout << "Dequeue: " << pq.dequeue() << endl;
//    cout << "Size: " << pq.size() << endl;
//    
//    cout << "Peek: " << pq.peek() << endl;
//    cout << "Dequeue: " << pq.dequeue() << endl;
//    cout << "Size: " << pq.size() << endl;
//    
//    cout << "Peek: " << pq.peek() << endl;
//    cout << "Dequeue: " << pq.dequeue() << endl;
//    cout << "Size: " << pq.size() << endl;
//    
//    
//    
//    pq.begin();
////    string value;
////    int priority;
//    while (pq.next(value, priority)) {
//       cout << priority << " value: " << value << endl;
//     }
//    
//    
//    
//    p.enqueue("Gwen", 3);
//    cout << "Queue:\n" << p.as_string() << endl;
//    
//    p=pq;
//    cout << "Queue:\n" << p.as_string() << endl;
//    
//    if (p == pq){cout<<"passed test"<<endl<<endl;};
//    
//    
//
//    cout << "Peek: " << pq.peek() << endl;
//    cout << "Dequeue: " << pq.dequeue() << endl;
//    cout << "Size: " << pq.size() << endl;
//
//    cout << "Queue:\n" << pq.as_string() << endl;
//
//    pq.clear();
//    cout << "Size after clear: " << pq.size() << endl;
//    
//    
//    
//   
//    p.enqueue("Gwen", 3);
//    p.enqueue("Jen", 2);
//    p.enqueue("Ben", 1);
//    p.enqueue("Sven", 2);
//
//    cout << "Peek: " << p.peek() << endl;
//   // cout << "Dequeue: " <<  << endl;
//    
//    cout << "Size: " << p.size() << endl;
//
//    cout << "Queue:\n" << p.as_string() << endl;
//
//    
//    if (p == pq){cout<<"passed test"<<endl<<endl;}else{cout<<"not same "<<endl<<endl;};
//    
//    
//    p.clear();
//    cout << "Size after clear: " << p.size() << endl;
//    
//    
//    
//    
//     prqueue<string> a;
//     a.enqueue("2", 2);
//     a.enqueue("1", 1);
//     a.enqueue("3", 3);
//    
//     prqueue<string> b;
//     b.enqueue("2", 2);
//     b.enqueue("3", 3);
//     b.enqueue("1", 1);
//
//     prqueue<string> c;
//     c.enqueue("1", 1);
//     c.enqueue("2", 2);
//     c.enqueue("3", 3);
//    
//    cout<<endl<<(b == a) ;
//    cout<<endl<<(b == c)<<endl<<endl;
//    
//    a.clear();
//    b.clear();
//    c.clear();
//    
//    return 0;
//}
//
//
//
//
//
//
//
//
//
