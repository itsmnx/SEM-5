create table customer(ID varchar2(10),name varchar2(10),age number(3),address varchar2(20),salary number(8,3))
insert into customer values('6','mnx',22,'UK',4500.00)
insert into customer values('7','leo',24,'UP',1200.00)
insert into customer values('8','ken',34,'MP',2200.00)
insert into customer values('11','om',95,'JK',3200.00)
insert into customer values('10','Ted',45,'RJ',5200.00)
select * from customer;

for update;
create or replace trigger display_salary_change
before update on customer
for each row
when(new.id>0)
declare
sal_diff number;
begin
sal_diff:=new.salary-:old.salary;
dbms_output.put_line('old salary: '|| :old.salary);
dbms_output.put_line('new salary: '|| :new.salary);
dbms_output.put_line('salary difference: '|| sal_diff);
end
SET SERVEROUTPUT ON;
UPDATE customer
SET salary = salary + 1000
WHERE id = '7';
select * from customer;
