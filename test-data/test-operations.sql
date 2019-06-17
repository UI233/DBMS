//检验index的create与delete
//create index->1.unique且未定义index 2.unique且定义index 3.非unique
//drop index->1.已定义index 2.未定义index

//查找时看效率->无index搜索=，有index搜索=，需要保证一定数据量，在之后测试。
//select->条件：<>,=,<,<=,>=,>, 涉及int,char,float;
//insert->1.值不够 2.类型不匹配 3.char类型超过限制（在name上）4.插入unique上重复值。5.正常操作（涉及int,char,float）
//create table->1.属性大于32个 2.char类型长度超过限制 3.正常操作
//drop table->1.检查drop后的index还在不在 2.select返回表不存在信息
//delete from->1.select检查是否删除成功。

//32
create table testattrNums(
	item1 int,
	item2 int,
	item3 int,
	item4 int,
	item5 int,
	item6 int,
	item7 int,
	item8 int,
	item9 int,
	item10 int,
	item11 int,
	item12 int,
	item13 int,
	item14 int,
	item15 int,
	item16 int,
	item17 int,
	item18 int,
	item19 int,
	item20 int,
	item21 int,
	item22 int,
	item23 int,
	item24 int,
	item25 int,
	item26 int,
	item27 int,
	item28 int,
	item29 int,
	item30 int,
	item31 int
)

create table testCharLength ( 
	height float unique,
	pid int,
	name char(256),
	identity char(128) unique,
	age int unique,
	primary key(pid)
);
//正常
create table person ( 
	height float unique,
	pid int,
	name char(32),
	identity char(128) unique,
	age int unique,
	primary key(pid)
);
//insert
//值不够
insert into person values (175.1, 1, "Person1", "000001");
//类型不匹配
insert into person values ("htt", 1, 199, "000001", 18);
//长度超过限制-char -32
insert into person values (175.1, 1, "123456789012345678901234567890", "000001", 18);
insert into person values (175.1, 1, "Person1", "000001", 18);
//插入unique上重复值
insert into person values (175.1, 1, "Person1", "000001", 18);
//非unique上重复值
insert into person values (175.2, 2, "Person1", "000002", 19);

//正常
insert into person values (165.1, 2, "Person2", "000002", 19);
insert into person values (165.3, 3, "Person3", "000003", 20);
insert into person values (175.9, 4, "Person4", "000004", 21);
insert into person values (175.0, 5, "Person5", "000005", 22);
insert into person values (172.1, 6, "Person6", "000006", 23);
insert into person values (175.2, 7, "Person7", "000007", 24);
insert into person values (175.1, 8, "Person8", "000008", 25);
insert into person values (174.1, 9, "Person9", "000009", 26);
insert into person values (175.1, 10, "Person10", "000010", 27);
insert into person values (172.1, 11, "Person11", "000011", 28);
insert into person values (175.1, 12, "Person12", "000012", 29);
insert into person values (174.1, 13, "Person13", "000013", 30);
insert into person values (175.1, 14, "Person14", "000014", 31);
insert into person values (175.1, 15, "Person15", "000015", 32);
insert into person values (173.1, 16, "Person16", "000016", 33);
insert into person values (175.1, 17, "Person17", "000017", 34);
insert into person values (175.1, 18, "Person18", "000018", 35);
insert into person values (179.1, 19, "Person19", "000019", 36);
insert into person values (171.1, 20, "Person20", "000020", 37);


//index组
//失败-未创建时drop
drop index idx_height;

//成功-unique
create index idx_height on person(height);
create index idx_identity on person(identity);
create index idx_age on person(age);

//失败->no index on attribute not unique
create index idex_name on person(name);

//！【不确定】失败->在一个已经有index的属性上再定义一个name不一样的index会咋样
create index idx_pid on person(pid);

//成功-已创建
drop index idx_height;
drop index idx_identity;
drop index idx_age;

//成功-说明确实删掉了，失败则凉了没删掉。
create index idx_age on person(age);

//select组
//=,int,float,char
//int-unique
select * from person where pid = 15;
//float-unique
select * from person where height = 173.5;
//string
select * from person where name="Person19";

//=,<>,<,>,<=,>=
//int
select * from person where pid = 15;
select * from person where pid <> 15;
select * from person where pid < 15;
select * from person where pid > 15;
select * from person where pid <= 15;
select * from person where pid >= 15;
select * from person where pid = 15;
//string
select * from person where name="Person19";
select * from person where name<>"Person19";
select * from person where name<"Person19";
select * from person where name>"Person19";
select * from person where name<="Person19";
select * from person where name>="Person19";
//float
select * from person where height = 175.1;
select * from person where height <> 175.1;
select * from person where height < 175.1;
select * from person where height > 175.1;
select * from person where height <= 175.1;
select * from person where height >= 175.1;

//多重条件
//exist
select * from person where age = 20 and height < 175.5 and identity="000003";
//non-exist
select * from person where age = 20 and height > 175.5;



//test drop
drop table person;
select * from person;
//若提示不存在该indexname则说明删除表时已经删除了这个index.
drop index idx_age;

//检查delete
select * from person where pid = 15;
delete * from person where pid = 15;
select * from person where pid = 15;

select * from person where pid < 15;
delete * from person where pid < 15;
select * from person where pid < 15;