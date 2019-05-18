# Buffer Manager

This is a simple documentation of **Buffer Manager**

In our project, buffer manager is responsible for almost all files' operations including reading files, creating files and modifying files.

## Usage

For the sake of efficiency, the buffer manager manages the resource in **Pages**. The size of  page is **4k byte** and the capacity of the buffer manager is **40** pages.

### Get a Page

To get a particular page of a specified file, just call the member function of the function. 

```cpp
// The range of index is [0, size_of_file / 4kbyte).  
Page* getPage(const std::string path, unsinged int index);
```

Then **Buffer Manager** would read specified page of file into memory and a pointer to a **Page** variable carrying those data.

**Buffer Manager** also provides similar function `createPage` with you enabling you to create page appending to a file and some functions like `getNextPage` and `getLastPage` making it easier to iterate the file.

### About Page

#### Unpin the Page
The page would be automatically pinned, which indicates that the page would not be flushed away when the replacement takes place, after creation. So if you don't need this page until the next request, don't  forget to unpin the page by calling the function `unpin` of **Page class**.

**Buffer Manager** also provides you the ability to force the data in page to be written back immediately by calling the `forceWrite` of page and to remove the page from buffer by calling the `close(Page*)`member function of **Buffer Manager**.(But I don't recommend you to use this function unless you are sure that you needn't to request this page in a sufficiently long period).

#### Data in Page

You can directly access the date, since those data is stored in the  public member of **Page** naming `data` whose type is `std::array<unsigned char, 4096>`. 

However, if you want to modify those data, I strongly recommend you to use following member function of `Page`,  which can set this page to be dirty after modification automatically, rather than doing it manually.

```cpp
void modify(char * pdata, int beg, int end);
```

If you want to modify those data by manually, just do not forget to **set the page to be dirty** by calling `setDirty` or those modifications would not be written back to file.

**To get detailed information of classes and functions, please read the header file which includes full information about their behaviors.**