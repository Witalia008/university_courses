CREATE TABLE roles
(
  id SERIAL PRIMARY KEY NOT NULL,
  rolename VARCHAR(200) NOT NULL
);
ALTER TABLE roles
ADD CONSTRAINT unique_id UNIQUE (id);
ALTER TABLE roles
ADD CONSTRAINT unique_rolename UNIQUE (rolename);

CREATE TABLE users
(
  id SERIAL PRIMARY KEY NOT NULL,
  username VARCHAR(200) NOT NULL,
  password VARCHAR(200) NOT NULL,
  roleid INT NOT NULL
);
ALTER TABLE users
ADD CONSTRAINT unique_id UNIQUE (id);
ALTER TABLE users
ADD CONSTRAINT unique_username UNIQUE (username);

ALTER TABLE public.users
ADD FOREIGN KEY (roleid) REFERENCES roles (id);

CREATE TABLE services
(
  id SERIAL PRIMARY KEY NOT NULL,
  sname VARCHAR(200) NOT NULL,
  author INT NOT NULL,
  atxt VARCHAR(5000) NOT NULL,
  stype INT NOT NULL,
  version VARCHAR(10) NOT NULL,
  conditions INT NOT NULL
);
ALTER TABLE services
ADD CONSTRAINT unique_id UNIQUE (id);

CREATE TABLE licenses
(
  id SERIAL PRIMARY KEY NOT NULL,
  cond VARCHAR(1000) NOT NULL,
  expires DATE NOT NULL,
  rules VARCHAR(1000) NOT NULL
);
ALTER TABLE licenses
ADD CONSTRAINT unique_id UNIQUE (id);

ALTER TABLE public.services
ADD FOREIGN KEY (conditions) REFERENCES licenses (id);

CREATE TABLE stats
(
  id SERIAL PRIMARY KEY NOT NULL,
  service INT NOT NULL,
  whendate DATE NOT NULL,
  nvisits INT NOT NULL
);
ALTER TABLE stats
ADD CONSTRAINT unique_id UNIQUE (id);

ALTER TABLE public.stats
ADD FOREIGN KEY (service) REFERENCES services (id);

CREATE TABLE changes
(
  id SERIAL PRIMARY KEY NOT NULL,
  service INT NOT NULL,
  changetext VARCHAR(200) NOT NULL
);
ALTER TABLE changes
ADD CONSTRAINT unique_id UNIQUE (id);

ALTER TABLE public.changes
ADD FOREIGN KEY (service) REFERENCES services (id);