-- drop schema CommercialHouse;
-- 商品房管理系统库，字符编码指定utf-8
create database CommercialHouse
  charset utf8
  collate utf8_general_ci;
use CommercialHouse;

-- 创建卖家表，卖家编号主键
create table seller (
  sellerId varchar(10) primary key,
  password varchar(10) not null,
  name     varchar(10)
);

-- 创建楼盘表，楼盘编号主键，卖家编号外键
create table Building (
  buildingId   varchar(10),
  sellerId     varchar(10),
  buildingName varchar(10),
  location     varchar(10) not null,
  count        int         not null check (count >= 0),
  primary key (buildingId, sellerId),
  foreign key (sellerId) references seller (sellerId)
);

-- 创建买家表，买家编号主键
create table Buyer (
  buyerId  varchar(10) primary key,
  id       varchar(18) unique check (length(id) = 18),
  name     varchar(10),
  phone    varchar(11) unique check (length(phone = 11)),
  password varchar(10)
);

-- 创建商品房表，房号主键，楼盘编号外键
create table room (
  roomId     varchar(10),
  buildingId varchar(10),
  category   varchar(10) not null,
  cost       double      not null,
  primary key (roomId, buildingId),
  foreign key (buildingId) references Building (buildingId)
);

-- 创建订单表，订单编号主键，买家编号外键，楼盘编号外键，房号外键，成交日期自动生成
create table list (
  listId     varchar(10),
  buyerId    varchar(10),
  buildingId varchar(10),
  roomId     varchar(10),
  date       varchar(30) default date_format(now(), '%y-%m-%d'),
  primary key (listId, buyerId, buildingId, roomId),
  foreign key (buyerId) references Buyer (buyerId),
  foreign key (buildingId) references room (buildingId),
  foreign key (roomId) references room (roomId)
);
-- drop table list;

-- 1、根据订单号查询(查询需要内容：订单号，买家id，楼盘id，楼盘name,楼盘位置)
-- 2、查询整张表(需要内容：订单号，卖家id，买家id，楼盘id，楼盘name,楼盘位置)

-- select list.listId, seller.sellerId, buyer.buyerId, building.buildingId, building.buildingName,
--        building.location from list, seller, buyer, building where list.buildingId = Building.buildingId
--         and list.buyerId = Buyer.buyerId and building.sellerId = seller.sellerId;

-- select list.listId, buyer.buyerId, Building.buildingId, building.buildingName, building.location from list, buyer, building
-- where list.buyerId = Buyer.buyerId and list.buildingId = building.buildingId and list.listId = 'listId';

-- 根据buildingName求平均cost
-- select seller.sellerId, building.buildingId, building.buildingName, room.category, format(avg(room.cost), 2)
--   from seller, Building, room where seller.sellerId = Building.sellerId and room.buildingId = Building.buildingId
--   group by Building.buildingId;
--
-- select seller.sellerId, building.buildingId, building.buildingName, room.category, format(avg(room.cost), 2)
--   from seller, Building, room where Building.BuildingName = '东方府居' and seller.sellerId = Building.sellerId and room.buildingId = Building.buildingId
--   group by Building.buildingId;

