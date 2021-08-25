# Отчет по лабораторной работе №1
## Работа со списками и реляционным представлением данных
## по курсу "Логическое программирование"

### студент: Мохляков П.А.

## Результат проверки

| Преподаватель     | Дата         |  Оценка       |
|-------------------|--------------|---------------|
| Сошников Д.В. |              |               |
| Левинская М.А.|              |       4       |


Отсутствует реализация append

## Введение

Стоит начать с того, что не во всех траниционных языках есть списки, но во многих их них их можно реализовать. Мы можем разделить список в прологе на голову и хвост, или обратиться ко всему списку целиком. В императивных языках мы обычно можем сказать, что у элимента есть ребенок (и предок если список двунаправленный). Также, в отличии от большенства традиционных языков программирования, в Пролог один список может хранить данные разных типов.

Таким образом мы можем сказать, что список в Пролог больше всего похож на бинарное дерево, листья которого либо указатель на элемент, либо NULL указатель.

## Задание 1.1: Предикаты обработки списка
`length` - Длина списка
```prolog
my_length([_|Tail],L):-
    my_length(Tail,L1),
    L is L1+1.
my_length([],L):-L is 0.
```

`member` - Принадлежность элимнта к списку
```prolog
my_member(F,[_|Tail]):-
    my_member(F,Tail).
my_member(F,[F|_]).
```

`append` - Конкатенация двух списков - реализация?
```prolog
my_remove([Item|Tail],Item,Tail).
my_remove([Head|Tail],Item,[Head|Tailres]):-
my_remove(Tail,Item,Tailres).
```
Описание remove?
`permute` - Все варианты перестановок списка
```prolog
my_permute([],[]).
my_permute(List,[Head|Tail]):-my_remove(List,Head,Res),my_permute(Res,Tail).
```

`sublist` - Является ли однин список подсписком другого

```prolog
my_sublist(Sub,List):-my_append(Sub,_,L),my_append(_,L,List).
```


`delete_last_three(L1,L2)` - Удаляет последние три элемента из списка.

Примеры использования:
```prolog
?- delete_last_three_std([1,2,3,4,6,3],X).
X = [1, 2, 3] ;

?- delete_last_three_std([1,2],X).
X = [].

?- delete_last_three_std([1,2,1,1],X).
X = [1] .

?- delete_last_three([6,4,24,3,24,2,1],X).
X = [6, 4, 24, 3].

?- delete_last_three([6,4],X).
X = [].

?- delete_last_three([6],X).
X = [].
```

Реализация:
```prolog
delete_last_three_std(List,Ans):-append(Ans,Last,List),length(Last,3).
delete_last_three_std(List,[]):-length(List,L),L=<3.

delete_last_three([],[]):-!.
delete_last_three([_],[]):-!.
delete_last_three([_,_],[]):-!.
delete_last_three([_,_,_],[]):-!.
delete_last_three([Head|Tail],[Head|Tans]):-delete_last_three(Tail,Tans).
```

В варианте и использованием стандартных предикатов мы выводим такой ответ, который при добавлении трех элиментов будет изначальным списком. Если длина списка меньше или равна 3, то мы возвращаем пустой список.

В случае со способом без стандартных предикатов мы рекурсивно уменьшаем список пока он не станет длины 3, тогда оставшийся хвост становится пустым списком. В случае если длина меньше или равна 3, то мы возвращаем пустой список.

## Задание 1.2: Предикат обработки числового списка

`vozr(List)` - Проверяет является ли список постоянно возврастающим.

Примеры использования:
```prolog
?- vozr_stl([1,2,3,4]).
true ;

?- vozr_stl([1,2,3,2]).
false.

?- vozr([1,2,3,4]).
true ;

?- vozr([]).
false.

?- vozr([1]).
true 
```

Реализация:
```prolog
vozr([_]).
vozr([Head,H2|Tail]):-vozr([H2|Tail]),Head =< H2.

vozr_stl([_]).
vozr_stl([Head|Tail]):-vozr_stl(Tail),append([H],_,Tail),Head =< H.
```

При использовании стандартных предикатов мы рекурсивно получаем первый элимент хвоста с помощью append и сравниваем его с головой, пока длина списка не равна 1, в таком случае список и так упорядочен.

Без использования стандартных предикатов мы сразу отделяем от списка два элемента без append.



## Задание 2: Реляционное представление данных

Одним из плюсов реляционного представления данных является относительно простой и независимый доступ к данным. Но всязи с этим мы не можем гараннтировать полноту входных и выходных данных, например может быть ситуация когда какой-нибудь студент вообще не сдавал какой-либо экзамен, поэтому мы не можем корректно посчитать его средний балл.

В моем случае каждая строка хранит группу, Фамилию студента, предмет и оценку. Минус такого устройства такой же как я описал выше.

Начнем с поиска средних баллов для всех предметов.

Создадим несколько необходимых в дальнейшем предикатов. Это сумма элиментов списка и вывод элиментов списка по одному
```prolog
sum_list([],Sum):- Sum is 0.
sum_list([Head|Tail],Sum):-sum_list(Tail,S2),Sum is S2+Head.

singl_elem([Head|_],X):- X = Head.
singl_elem([_|Tail],X):-singl_elem(Tail,X).
```

Найдем список баллов для предмета

```prolog
ball_list_for_less(Less,List):-findall(X,grade(_,_,Less,X),List).
```

Далее мы уже можем посчитать средний балл для определенного предмета. Получив список баллов, найдя их сумму, и поделя на количество баллов.
```prolog
mid_ball(Less,X):-
    ball_list_for_less(Less,Balllist),
    sum_list(Balllist,Sum),
    length(Balllist, Leng),
    X is Sum / Leng.
```
Для вывода стредних баллов для всех предметов нам нужно получить список предметов.
```prolog
all_less(List):-
    findall(X,grade(_,_,X,_),Listf),
    setof(L,member(L,Listf),List).
```
Теперь мы можем вывести средний балл для всех предметов.
```prolog
mid_ball:-
    all_less(Less_list),
    singl_elem(Less_list,Less),
    mid_ball(Less,X),
    write(Less),write("-"),write(X),nl.
```

Теперь найдем количество не сдавших в каждой группе и каждом предмете.

Сначала для удобства определим предикат не сдавшего студента.
```prolog
    ne_sdal(Group,Fam,Less):-grade(Group,Fam,Less,2).
```

Теперь можно получить список не сдавших, и посчитать его длину.
```prolog
    ne_sdal_group(Group,Count):-
    findall(Fam,ne_sdal(Group,Fam,_),List1),
    setof(L,member(L,List1),List2),
    length(List2,Count).

    ne_sdal_less(Less,Count):-
    findall(Fam,ne_sdal(_,Fam,Less),List1),
    setof(L,member(L,List1),List2),
    length(List2,Count).
```

Для удобства я опять опишу полный вывод для колличева не сдавших в группах и предметах.

```prolog
ne_sdal_all_group:-
    findall(Groups,grade(Groups,_,_,_),List1),
    setof(L,member(L,List1),List),
    singl_elem(List,Group),
    ne_sdal_group(Group,Count),
    write(Group),write("-"),write(Count),nl.

ne_sdal_all_less:-
    findall(Less,grade(_,_,Less,_),List1),
    setof(L,member(L,List1),List),
    singl_elem(List,Lesson),
    ne_sdal_less(Lesson,Count),
    write(Lesson),write("-"),write(Count),nl.
```



## Выводы

В Прологе, в отличии от императивных языков, мы омписываем не то как что-то сделать, а то что мы хотим получить, и каким условиям оно должно подходить. Этот подход очень сильно отличается от императивного, что в некоторых случаях может сильно упростить работу программита. Как пример можно привести нашу курсовую работу по дискретной математике в прошлом семестре, посвященная теории групп. В моем случае мне пришлось писать методы доказательста, что два элимента равны с помощью перебора. В то время как эту же задачу можно было решить намного проще используя логические языки программирования.

В данной лаборатоной работе я еще больше погрузился в логическое программирование, которое я начал в курсовой работе. Теперь я могу на базовом уровне работать со списками, поиском всех решений реляционных таблицах и вводом выводом. Тем не менее иногда бывает сложно мыслить в непривычной для себя парадигме.


