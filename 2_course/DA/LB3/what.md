73:

string.hpp str-117

Если мы ничего не введем, то будем пытаться изменять пустую строку
```C++
in >> str.str;
str.lower();
```


90:

rb.hpp ~300

страрое
```C++
Root = new rb_tree_elem<T>;
Root->Par = Nil;
Root->Left = Nil;
Root->Right = Nil;
if(!isFileEmpty(ch))
    load_tree(Root,rf);
```

новое
```C++
Root = Nil;
if(!isFileEmpty(ch))
{
    Root = new rb_tree_elem<T>;
    Root->Par = Nil;
    Root->Left = Nil;
    Root->Right = Nil;
    load_tree(Root,rf);
}
rf.close()
```
Если файл пустой, то создается пустой (мусорный элимет) элимент, который ломает логику.

