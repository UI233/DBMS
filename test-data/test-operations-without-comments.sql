
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
create table person ( 
	height float unique,
	pid int,
	name char(32),
	identity char(128) unique,
	age int unique,
	primary key(pid)
);
insert into person values (175.1, 1, "Person1", "000001");
insert into person values ("htt", 1, 199, "000001", 18);
insert into person values (175.1, 1, "123456789012345678901234567890", "000001", 18);
insert into person values (175.1, 1, "Person1", "000001", 18);
insert into person values (175.1, 1, "Person1", "000001", 18);
insert into person values (175.2, 2, "Person1", "000002", 19);

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


drop index idx_height;

create index idx_height on person(height);
create index idx_identity on person(identity);
create index idx_age on person(age);

create index idex_name on person(name);

create index idx_pid on person(pid);

drop index idx_height;
drop index idx_identity;
drop index idx_age;

create index idx_age on person(age);

select * from person where pid = 15;
select * from person where height = 173.5;
select * from person where name="Person19";

select * from person where pid = 15;
select * from person where pid <> 15;
select * from person where pid < 15;
select * from person where pid > 15;
select * from person where pid <= 15;
select * from person where pid >= 15;
select * from person where pid = 15;
select * from person where name="Person19";
select * from person where name<>"Person19";
select * from person where name<"Person19";
select * from person where name>"Person19";
select * from person where name<="Person19";
select * from person where name>="Person19";
select * from person where height = 175.1;
select * from person where height <> 175.1;
select * from person where height < 175.1;
select * from person where height > 175.1;
select * from person where height <= 175.1;
select * from person where height >= 175.1;

select * from person where age = 20 and height < 175.5 and identity="000003";
select * from person where age = 20 and height > 175.5;



drop table person;
select * from person;
drop index idx_age;

select * from person where pid = 15;
delete from person where pid = 15;
select * from person where pid = 15;

select * from person where pid < 15;
delete from person where pid < 15;
select * from person where pid < 15;