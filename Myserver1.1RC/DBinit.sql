CREATE TABLE his_pack
(
	pack_num varchar2(19)
);

CREATE TABLE login_info
(
	dev_id varchar2(18),
	soft_ver varchar2(7),
	hard_ver varchar2(7)
);

CREATE TABLE card_info
(
	card_no number(8),
	card_sum number(8),
	card_stat number(8)
);

CREATE TABLE client_info
(
	phone_num number(13),
	phone_money number(8)
);

CREATE TABLE bill_info
(
	phone_num number(13),
	date number(7),
	charge_sum number(8),
	message number(8),
	calls number(8),
	GPRS number(8),
	SP number(8),
	others number(8)
);

CREATE TABLE detail_info
(
	phone_num number(13),
	date number(7),
	send_call number(13),
	recv_call number(13),
	call_type varchar2(20),
	call_time varchar2(10),
	each_charge varchar2(6),
	remark varchar2(100)
);


begin;

insert into login_info values('1000', '1.0.0', '1.0.0');
insert into login_info values('1001', '1.0.0', '1.0.0');
insert into login_info values('1002', '1.0.0', '1.0.0');
insert into login_info values('1003', '1.0.0', '1.0.0');
insert into login_info values('1004', '1.0.0', '1.0.0');
insert into login_info values('1005', '1.0.0', '1.0.0');
insert into login_info values('1006', '1.0.0', '1.0.0');
insert into login_info values('1007', '1.0.0', '1.0.0');
insert into login_info values('1008', '1.0.0', '1.0.0');
insert into login_info values('1009', '1.0.0', '1.0.0');


insert into client_info values(13100000000, 0);
insert into client_info values(13100000001, 10);
insert into client_info values(13100000002, 20);
insert into client_info values(13100000003, 30);
insert into client_info values(13100000004, 40);
insert into client_info values(13100000005, 50);
insert into client_info values(13100000006, 60);
insert into client_info values(13100000007, 70);
insert into client_info values(13100000008, 80);
insert into client_info values(13100000009, 90);

insert into bill_info values(13100000000, 201001, 10, 50, 40, 30, 20, 10);
insert into bill_info values(13100000000, 201002, 10, 40, 10, 300, 20, 10);
insert into bill_info values(13100000000, 201003, 10, 250, 140, 30, 200, 100);
insert into bill_info values(13100000000, 201004, 10, 50, 40, 360, 200, 190);
insert into bill_info values(13100000000, 201005, 10, 50, 450, 350, 250, 10);
insert into bill_info values(13100000000, 201006, 10, 50, 40, 30, 20, 10);
insert into bill_info values(13100000000, 201007, 10, 50, 140, 830, 20, 310);
insert into bill_info values(13100000000, 201008, 10, 50, 40, 30, 20, 210);
insert into bill_info values(13100000000, 201009, 10, 50, 40, 30, 20, 110);
insert into bill_info values(13100000000, 201010, 10, 150, 50, 30, 20, 110);
insert into bill_info values(13100000000, 201011, 10, 50, 540, 930, 20, 110);
insert into bill_info values(13100000000, 201012, 10, 950, 40, 630, 120, 110);

insert into detail_info values(13100000000, 201001, 13100000000, 13100000001, '����ͨ��', '10����', '2Ԫ', ' ');
insert into detail_info values(13100000000, 201001, 13100000000, 13100000001, '���ͨ��', '10����', '6Ԫ', ' ');
insert into detail_info values(13100000000, 201001, 13100000000, 13100000001, '����ҵ��', '0����', '0.1Ԫ', ' ');
insert into detail_info values(13100000000, 201001, 13100000000, 13100000001, '����ҵ��', '0����', '1Ԫ', ' ');

insert into detail_info values(13100000000, 201002, 13100000000, 13100000001, '����ͨ��', '100����', '20Ԫ', ' ');
insert into detail_info values(13100000000, 201002, 13100000000, 13100000001, '���ͨ��', '10����', '6Ԫ', ' ');
insert into detail_info values(13100000000, 201002, 13100000000, 13100000001, '����ҵ��', '0����', '0.1Ԫ', ' ');
insert into detail_info values(13100000000, 201002, 13100000000, 13100000001, '����ҵ��', '0����', '1Ԫ', ' ');

insert into detail_info values(13100000000, 201003, 13100000000, 13100000001, '����ͨ��', '10����', '2Ԫ', ' ');
insert into detail_info values(13100000000, 201003, 13100000000, 13100000001, '���ͨ��', '100����', '60Ԫ', ' ');
insert into detail_info values(13100000000, 201003, 13100000000, 13100000001, '����ҵ��', '0����', '0.1Ԫ', ' ');
insert into detail_info values(13100000000, 201003, 13100000000, 13100000001, '����ҵ��', '0����', '1Ԫ', ' ');

insert into detail_info values(13100000000, 201004, 13100000000, 13100000001, '����ͨ��', '20����', '4Ԫ', ' ');
insert into detail_info values(13100000000, 201004, 13100000000, 13100000001, '���ͨ��', '50����', '30Ԫ', ' ');
insert into detail_info values(13100000000, 201004, 13100000000, 13100000001, '����ҵ��', '0����', '0.1Ԫ', ' ');
insert into detail_info values(13100000000, 201004, 13100000000, 13100000001, '����ҵ��', '0����', '0.1Ԫ', ' ');
insert into detail_info values(13100000000, 201004, 13100000000, 13100000001, '����ҵ��', '0����', '1Ԫ', ' ');

insert into detail_info values(13100000000, 201005, 13100000000, 13100000001, '����ͨ��', '10����', '2Ԫ', ' ');
insert into detail_info values(13100000000, 201005, 13100000000, 13100000001, '���ͨ��', '40����', '24Ԫ', ' ');
insert into detail_info values(13100000000, 201005, 13100000000, 13100000001, '����ҵ��', '0����', '0.1Ԫ', ' ');
insert into detail_info values(13100000000, 201005, 13100000000, 13100000001, '����ҵ��', '0����', '0.1Ԫ', ' ');
insert into detail_info values(13100000000, 201005, 13100000000, 13100000001, '����ҵ��', '0����', '1Ԫ', ' ');

insert into detail_info values(13100000000, 201006, 13100000000, 13100000001, '����ͨ��', '10����', '2Ԫ', ' ');
insert into detail_info values(13100000000, 201006, 13100000000, 13100000001, '���ͨ��', '30����', '18Ԫ', ' ');
insert into detail_info values(13100000000, 201006, 13100000000, 13100000001, '����ҵ��', '0����', '0.1Ԫ', ' ');
insert into detail_info values(13100000000, 201006, 13100000000, 13100000001, '����ҵ��', '0����', '0.1Ԫ', ' ');
insert into detail_info values(13100000000, 201006, 13100000000, 13100000001, '����ҵ��', '0����', '1Ԫ', ' ');

insert into detail_info values(13100000000, 201007, 13100000000, 13100000001, '����ͨ��', '10����', '2Ԫ', ' ');
insert into detail_info values(13100000000, 201007, 13100000000, 13100000001, '���ͨ��', '110����', '66Ԫ', ' ');
insert into detail_info values(13100000000, 201007, 13100000000, 13100000001, '����ҵ��', '0����', '0.1Ԫ', ' ');
insert into detail_info values(13100000000, 201007, 13100000000, 13100000001, '����ҵ��', '0����', '0.1Ԫ', ' ');
insert into detail_info values(13100000000, 201007, 13100000000, 13100000001, '����ҵ��', '0����', '1Ԫ', ' ');

insert into detail_info values(13100000000, 201008, 13100000000, 13100000001, '����ͨ��', '10����', '2Ԫ', ' ');
insert into detail_info values(13100000000, 201008, 13100000000, 13100000001, '���ͨ��', '20����', '12Ԫ', ' ');
insert into detail_info values(13100000000, 201008, 13100000000, 13100000001, '����ҵ��', '0����', '0.1Ԫ', ' ');
insert into detail_info values(13100000000, 201008, 13100000000, 13100000001, '����ҵ��', '0����', '0.1Ԫ', ' ');
insert into detail_info values(13100000000, 201008, 13100000000, 13100000001, '����ҵ��', '0����', '1Ԫ', ' ');

insert into detail_info values(13100000000, 201009, 13100000000, 13100000001, '����ͨ��', '10����', '2Ԫ', ' ');
insert into detail_info values(13100000000, 201009, 13100000000, 13100000001, '���ͨ��', '20����', '12Ԫ', ' ');
insert into detail_info values(13100000000, 201009, 13100000000, 13100000001, '����ҵ��', '0����', '0.1Ԫ', ' ');
insert into detail_info values(13100000000, 201009, 13100000000, 13100000001, '����ҵ��', '0����', '0.1Ԫ', ' ');
insert into detail_info values(13100000000, 201009, 13100000000, 13100000001, '����ҵ��', '0����', '19Ԫ', ' ');

insert into detail_info values(13100000000, 201010, 13100000000, 13100000001, '����ͨ��', '10����', '2Ԫ', ' ');
insert into detail_info values(13100000000, 201010, 13100000000, 13100000001, '���ͨ��', '20����', '12Ԫ', ' ');
insert into detail_info values(13100000000, 201010, 13100000000, 13100000001, '����ҵ��', '0����', '0.1Ԫ', ' ');
insert into detail_info values(13100000000, 201010, 13100000000, 13100000001, '����ҵ��', '0����', '0.1Ԫ', ' ');
insert into detail_info values(13100000000, 201010, 13100000000, 13100000001, '����ҵ��', '0����', '1Ԫ', ' ');

insert into detail_info values(13100000000, 201011, 13100000000, 13100000001, '����ͨ��', '10����', '2Ԫ', ' ');
insert into detail_info values(13100000000, 201011, 13100000000, 13100000001, '���ͨ��', '20����', '12Ԫ', ' ');
insert into detail_info values(13100000000, 201011, 13100000000, 13100000001, '����ҵ��', '0����', '0.1Ԫ', ' ');
insert into detail_info values(13100000000, 201011, 13100000000, 13100000001, '����ҵ��', '0����', '0.1Ԫ', ' ');
insert into detail_info values(13100000000, 201011, 13100000000, 13100000001, '����ҵ��', '0����', '1Ԫ', ' ');

insert into detail_info values(13100000000, 201012, 13100000000, 13100000001, '����ͨ��', '10����', '2Ԫ', ' ');
insert into detail_info values(13100000000, 201012, 13100000000, 13100000001, '���ͨ��', '20����', '12Ԫ', ' ');
insert into detail_info values(13100000000, 201012, 13100000000, 13100000001, '����ҵ��', '0����', '0.1Ԫ', ' ');
insert into detail_info values(13100000000, 201012, 13100000000, 13100000001, '����ҵ��', '0����', '0.1Ԫ', ' ');
insert into detail_info values(13100000000, 201012, 13100000000, 13100000001, '����ҵ��', '0����', '1Ԫ', ' ');



commit;


