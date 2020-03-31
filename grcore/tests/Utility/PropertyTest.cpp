//
// Created by Jedzia on 01.11.2018.
//

#include <cassert>
#include <cstdio>
#include <grcore/Utility/Property.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
//
#include <gtest/gtest.h>

using std::cout;
using std::endl;

TEST(Property, feed_function) {
    //remove("backup_test.db3");
    //SQLite::Database srcDB("backup_test.db3", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
    //srcDB.exec("CREATE TABLE backup_test (id INTEGER PRIMARY KEY, value TEXT)");
    //ASSERT_EQ(1, srcDB.exec("INSERT INTO backup_test VALUES (1, \"first\")"));
    //ASSERT_EQ(1, srcDB.exec("INSERT INTO backup_test VALUES (2, \"second\")"));
    //EXPECT_THROW(SQLite::Backup backup(srcDB, srcDB), SQLite::Exception);
    //EXPECT_THROW(SQLite::Backup backup(srcDB, "main", srcDB, "main"), SQLite::Exception);
    //const std::string name("main");
    //EXPECT_THROW(SQLite::Backup backup(srcDB, name, srcDB, name), SQLite::Exception);
    //remove("backup_test.db3");

    int a = 7;
    std::function<int(void)> f = [&a]() { return a; };
    auto prop = grcore::util::Property(f);

    ASSERT_EQ(a, f());
    ASSERT_EQ(a, prop.Get());
}

TEST(Property, feed_lambda) {
    int a = -42;
    auto prop = grcore::util::Property([&a]() { return a; });

    ASSERT_EQ(a, -42);
    ASSERT_EQ(a, prop.Get());
}

TEST(Property, tripped) {
    int a = -42;
    auto prop = grcore::util::Property([&a]() { return a; });

    a = -41;
    ASSERT_TRUE(prop.HasChanged());
}

TEST(Property, tripped_complex) {
    int a = -42;
    auto prop = grcore::util::Property([&a]() { return a; });

    ASSERT_FALSE(prop.HasChanged());
    a = -42;
    ASSERT_FALSE(prop.HasChanged());
    a = -41;
    ASSERT_TRUE(prop.HasChanged());
    ASSERT_FALSE(prop.HasChanged());
    ASSERT_FALSE(prop.HasChanged());
    ASSERT_FALSE(prop.HasChanged());
}

TEST(Property, tripped_multiple) {
    int a = 555555555;
    auto prop = grcore::util::Property([&a]() { return a; });

    ASSERT_FALSE(prop.HasChanged());
    a = 777777777;
    ASSERT_TRUE(prop.HasChanged());
    ASSERT_FALSE(prop.HasChanged());
    a = 666666666;
    ASSERT_TRUE(prop.HasChanged());
    ASSERT_FALSE(prop.HasChanged());
    a = 555555555;
    ASSERT_TRUE(prop.HasChanged());
    a = 555555554;
    ASSERT_TRUE(prop.HasChanged());
    a = 555555553;
    ASSERT_TRUE(prop.HasChanged());
    a = -155555555;
}

TEST(Property, released) {
    int a = 0;
    auto prop = grcore::util::Property([&a]() { return a; });

    ASSERT_FALSE(prop.HasChanged());
    a = 0;
    ASSERT_FALSE(prop.HasChanged());
    a = 1;
    ASSERT_TRUE(prop.HasChanged());
    ASSERT_FALSE(prop.HasChanged());
}

TEST(Property, released_multiple) {
    int a = -42;
    auto prop = grcore::util::Property([&a]() { return a; });

    ASSERT_FALSE(prop.HasChanged());
    ASSERT_FALSE(prop.HasChanged());
    ASSERT_FALSE(prop.HasChanged());
    a = -42;
    ASSERT_FALSE(prop.HasChanged());
    ASSERT_FALSE(prop.HasChanged());
    ASSERT_FALSE(prop.HasChanged());
}

struct Functor {
    Functor() {
        std::cout << "+++ Constructor " << __PRETTY_FUNCTION__ << " -> " << " called. +++" << std::endl;
    }

    Functor(const Functor &) = delete;  // non construction-copyable
    Functor &operator=(const Functor &) = delete;  // non copyable

    std::string m_string = "Hello";

    const std::string &operator()() const {
        return m_string;
    }

    const std::string &GetString() const {
        return m_string;
    }
};

TEST(Property, Functor_inst) {

    Functor func;

    ASSERT_EQ("Hello", func());
    func.m_string = "World";
    ASSERT_EQ("World", func());
}

TEST(Property, Functor_lambda) {

    Functor func;
    auto prop1 = grcore::util::Property([&func]() { return func(); });

    ASSERT_FALSE(prop1.HasChanged());
    ASSERT_EQ("Hello", prop1.Get());
    func.m_string = "World";
    ASSERT_TRUE(prop1.HasChanged());
    ASSERT_FALSE(prop1.HasChanged());
}

TEST(Property, Functor_bind1) {

    Functor *func2 = new Functor;
    std::function<std::string(void)> callback;
    callback = std::bind(&Functor::GetString, func2);//create delegate
    auto prop = grcore::util::Property(callback);
    ASSERT_FALSE(prop.HasChanged());
    ASSERT_EQ("Hello", prop.Get());
    func2->m_string = "World";
    ASSERT_EQ("World", func2->GetString()); // instance is updated.
    ASSERT_EQ("Hello", prop.Get()); // property has the old value without a HasChanged call.
    ASSERT_TRUE(prop.HasChanged()); // is now changed.
    ASSERT_EQ("World", prop.Get()); // and has the new value stored.
    ASSERT_FALSE(prop.HasChanged());
}

TEST(Property, Functor_ref_wrapper) {
    {
        Functor func;
        auto prop = grcore::util::Property<std::function<std::string(void)>>(std::ref(func));
        ASSERT_FALSE(prop.HasChanged());
        ASSERT_EQ("Hello", prop.Get());
        func.m_string = "World";
        ASSERT_EQ("World", func.GetString()); // instance is updated.
        ASSERT_EQ("Hello", prop.Get()); // property has the old value without a HasChanged call.
        ASSERT_TRUE(prop.HasChanged()); // is now changed.
        ASSERT_EQ("World", prop.Get()); // and has the new value stored.
        ASSERT_FALSE(prop.HasChanged());
    }
    {
        // Needs a template specialization
        /*Functor func;
        auto prop = grcore::util::Property(std::ref(func));
        ASSERT_FALSE(prop.HasChanged());
        ASSERT_EQ("Hello", prop.Get());
        func.m_string = "World";
        ASSERT_EQ("World", func.GetString()); // instance is updated.
        ASSERT_EQ("Hello", prop.Get()); // property has the old value without a HasChanged call.
        ASSERT_TRUE(prop.HasChanged()); // is now changed.
        ASSERT_EQ("World", prop.Get()); // and has the new value stored.
        ASSERT_FALSE(prop.HasChanged());*/
    }
}

TEST(Property, Functor_ref) {

    Functor func;
    const std::reference_wrapper<Functor> &wrapper = std::ref(func);
    auto prop = grcore::util::Property<std::function<std::string(void)>>(wrapper);
    ASSERT_FALSE(prop.HasChanged());
    ASSERT_EQ("Hello", prop.Get());
    wrapper.get().m_string = "World";
    ASSERT_EQ("World", func());
    ASSERT_EQ("Hello", prop.Get());
    ASSERT_TRUE(prop.HasChanged());
    ASSERT_EQ("World", prop.Get());
    ASSERT_FALSE(prop.HasChanged());
}

class PropertySuite : public ::testing::Test {
protected:
    double m_x = 6.0;

    double GetX() const {
        return m_x;
    }

protected:
    //grcore::util::Property m_prop = grcore::util::Property([]() { return 5; });
    grcore::util::Property<std::function<double(void)>> m_prop1{[&]() { return m_x; }};
    grcore::util::Property<std::function<int(void)>> m_prop2{[&]() { return m_x; }};
protected:

    virtual void TearDown() {}

    virtual void SetUp() {}
};

TEST_F(PropertySuite, TestName) {
    ASSERT_EQ(6.0, m_x);
    ASSERT_EQ(6.0, m_prop1.Get());
    ASSERT_EQ(6, m_prop2.Get());
    ASSERT_FALSE(m_prop1.HasChanged());
    ASSERT_FALSE(m_prop2.HasChanged());
    m_x = 6.001;
    ASSERT_TRUE(m_prop1.HasChanged());
    // so there is no warning caused by the double to int conversion
    ASSERT_EQ(6, m_prop2.Get());
    ASSERT_FALSE(m_prop2.HasChanged());
}
