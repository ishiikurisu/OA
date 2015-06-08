# Compile Instructions

# How to use search.exe and retrieve.exe

Instructions
------------

+ Usage of index.exe

      index.exe database_file index_file

index.exe will create an index_file to be used with feed.exe and search.exe.

+ Usage of feed.exe

      more index_file | feed.exe root_file_name

This utility will create a network of .page files which will facilitate the
search.

+ Usage of search.exe

      search.exe index_file
      $> query

The utility search.exe will build a btree out of the index file and then
retrieve the PRR of the desired information.

+ Usage of retrieve.exe

    retrieve.exe database_file

This is a dream utility. It will create the index_file, the btree out of it
and then will retrieve every possible information about a query. For example:
searching for joe frank would give you every album he has.

# Database structure

It uses the following syntax:

    Primary Key;Name;Album
    Primary Key;Name;Album

# BTREE file structure

    PAGE|path
    NODE|key:value
