//查找时看效率->无index搜索，有index搜索，需要保证一定数据量。

//int-unique
select * from person where pid = 9999;
//float-unique
select * from person where height = 13015.0;
//duplicate-string
select * from person where name="David";
//duplicate conditions
//exist
select * from person where age = 20 and name ="David";
//non-exist
select * from person where age=20 and name = "Jerry";

create index idx_height on person(height);
create index idx_identity on person(identity);
create index idx_age on person(age);

//int-unique
select * from person where pid = 9999;
//float-unique
select * from person where height = 13015.0;
//duplicate-string
select * from person where name="David";
//duplicate conditions
//exist
select * from person where age = 20 and name ="David";
//non-exist
select * from person where age=20 and name = "Jerry";
