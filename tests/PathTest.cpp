/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** PathTest.cpp
*/

#include <gtest/gtest.h>
#include "Path.hpp"

// --- Filename
TEST(path_filename_function, copies_have_same_filename)
{
    const std::string filename("foo.bar");
    const Path filenamePath(filename);
    EXPECT_EQ(filename, filenamePath.filename());
    EXPECT_EQ(filename, Path(filenamePath.filename()).filename());
}

TEST(path_filename_function, different_paths_can_have_same_filename)
{
    const std::string filename("foo.bar");
    const Path parent("/foo/bar/foo.bar");
    EXPECT_EQ(filename, parent.filename());
}

TEST(path_filename_function, path_with_dot)
{
    const std::string filename("foo.bar");
    const Path dottedParent("/foo/.bar/foo.bar");
    EXPECT_EQ(filename, dottedParent.filename());
}

TEST(path_filename_function, add_filename)
{
    const std::string filename("foo.bar");
    Path parent("/foo/bar");
    parent /= filename;
    EXPECT_EQ(filename, parent.filename());
}

TEST(path_filename_function, filename_without_extension)
{
    const std::string filename("foo.bar");
    const Path parent("/foo/bar");
    EXPECT_EQ("bar", parent.filename());
}

// --- Absolute
TEST(path_is_absolute_function, UNC_path)
{
        const Path uncAbsPath("//foo/bar/foobar");
        EXPECT_TRUE(uncAbsPath.is_absolute());
}
TEST(path_is_absolute_function, Unix_root)
{
    const Path unixAbsPath("/foo/bar");
    EXPECT_TRUE(unixAbsPath.is_absolute());
}

TEST(path_is_absolute_function, realtif_path)
{
        const Path relPath("../foo");
        EXPECT_FALSE(relPath.is_absolute());

        const Path otherRelPath("foo/bar");
        EXPECT_FALSE(otherRelPath.is_absolute());
}

TEST(path_is_absolute_function, empty_path)
{
    const Path emptyPath("");
    EXPECT_FALSE(emptyPath.is_absolute());
}

#if defined(_WIN32)
TEST(path_is_absolute_function, path_with_drive)
{
    const path driveAbsPath("C:\\foo\\bar");
    EXPECT_TRUE(driveAbsPath.is_absolute());
}
#endif

// --- Is Normal Syntax
TEST(path_is_normal_syntax_function, normal_path)
{
    const Path p1("/foo/bar");
    EXPECT_TRUE(p1.is_normal_syntax());

    const Path p2("weird/path/with../dots/..in/file.names..");
    EXPECT_TRUE(p2.is_normal_syntax());
}

TEST(path_is_normal_syntax_function, not_normal_path)
{
    const Path p1("/foo/../bar");
    EXPECT_FALSE(p1.is_normal_syntax());

    const Path p2("/foo/./bar/");
    EXPECT_FALSE(p2.is_normal_syntax());

    const Path p3("../.././././..");
    EXPECT_FALSE(p3.is_normal_syntax());
}

// --- Root
TEST(path_root_function, root_path)
{
    {
        const Path p("/");
        EXPECT_TRUE(p.is_root());
    }

    {
        const Path p("/foo");
        EXPECT_TRUE(p.is_root());
    }

    {
        const Path p("//");
        EXPECT_TRUE(p.is_root());
    }

    {
        const Path p("//foo");
        EXPECT_TRUE(p.is_root());
    }

#if defined(_WIN32)
    {
        const path p("C:\\");
        EXPECT_TRUE(p.is_root());
    }
#endif
}

TEST(path_root_function, not_root_path)
{
    {
        const Path p("/foo/bar");
        EXPECT_FALSE(p.is_root());
    }

    {
        const Path p("relative/path");
        EXPECT_FALSE(p.is_root());
    }
}


// --- Parent
TEST(path_parent_function, double_dot)
{
    const Path parent("/foo");
    {
        const Path child("/foo/bar");
        EXPECT_EQ(parent, (child / ".."));
        EXPECT_EQ(parent, child.parent_path());
    }
    
    {
        const Path child("/foo/bar/baz/.././../bar/.././bar/./");
        EXPECT_EQ(parent, child / "..");
        EXPECT_EQ(parent, child.parent_path());
    }

    {
        const Path child("/foo/bar/.");
        EXPECT_EQ(parent, child / "..");
        EXPECT_EQ(parent, child.parent_path());
    }
}

TEST(path_parent_function, no_parent_return_empty_path)
{
    const Path empty_path("");
    {
        const Path child("");
        EXPECT_EQ(empty_path, child / "..");
        EXPECT_EQ(empty_path, child.parent_path());
    }

    {
        const Path child(".");
        EXPECT_EQ(empty_path, child / "..");
        EXPECT_EQ(empty_path, child.parent_path());
    }

    {
        const Path child("..");
        EXPECT_EQ(empty_path, child / "..");
        EXPECT_EQ(empty_path, child.parent_path());
    }
}

TEST(path_parent_function, root_parent_is_root)
{
    {
        const Path root("/");
        EXPECT_EQ(root, root / "..");
        EXPECT_EQ(root, root.parent_path());
    }

#if defined(_WIN32)
    {
        const path windowsRoot("c:");
        EXPECT_EQ(windowsRoot, windowsRoot / "..");
        EXPECT_EQ(windowsRoot, windowsRoot.parent_path());
    }
#endif

    {
        const Path uncRoot("//");
        EXPECT_EQ(uncRoot, uncRoot / "..");
        EXPECT_EQ(uncRoot, uncRoot.parent_path());
    }
}

// --- Replace Extension
TEST(path_replace_extension_function, normal_replace)
{
    const std::string dottedExtension(".bar");
    const std::string emptyExtension("");

    Path p("/foo.baz");
    p.replace_extension(dottedExtension);
    EXPECT_EQ(dottedExtension, p.extension());
}

TEST(path_replace_extension_function, empty_extension_string)
{
    const std::string dottedExtension(".bar");
    const std::string emptyExtension("");

    Path p("/foo.bar");
    p.replace_extension(emptyExtension);
    EXPECT_EQ(emptyExtension, p.extension());
}

TEST(path_replace_extension_function, add_extension_on_a_non_existant_extension)
{
    const std::string dottedExtension(".bar");
    const std::string emptyExtension("");
    Path p("/foo");
    p.replace_extension(dottedExtension);
    EXPECT_EQ(dottedExtension, p.extension());
}

TEST(path_replace_extension_function, dot_logic)
{
    const std::string dottedExtension(".bar");
    const std::string emptyExtension("");
    {
        Path p("beep.boop.bleep");
        p.replace_extension(dottedExtension);
        EXPECT_EQ(dottedExtension, p.extension());
    }

    {
        Path p(".foo");
        p.replace_extension(dottedExtension);
        EXPECT_EQ(dottedExtension, p.extension());
    }
    
    {
        Path p("dotted.parent/foo");
        p.replace_extension(dottedExtension);
        EXPECT_EQ(dottedExtension, p.extension());
    }

    {
        Path p("dotted.parent/foo");
        const Path q = p;
        p.replace_extension(emptyExtension);
        EXPECT_EQ(emptyExtension, p.extension());
        EXPECT_EQ(q, p);
    }   
}