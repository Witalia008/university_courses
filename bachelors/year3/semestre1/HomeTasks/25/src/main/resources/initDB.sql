CREATE TABLE messages (
  id int(11) NOT NULL AUTO_INCREMENT,
  text varchar(4000) NOT NULL,
  room int(11) NOT NULL,
  usr int(11) NOT NULL,
  PRIMARY KEY (id),
  KEY usr (usr),
  KEY room (room),
  CONSTRAINT messages_ibfk_1 FOREIGN KEY (usr) REFERENCES users (id),
  CONSTRAINT messages_ibfk_2 FOREIGN KEY (room) REFERENCES rooms (id)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8

CREATE TABLE rooms (
  id int(11) NOT NULL AUTO_INCREMENT,
  topic varchar(200) NOT NULL DEFAULT 'N/A',
  PRIMARY KEY (id)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8

CREATE TABLE users (
  id int(11) NOT NULL AUTO_INCREMENT,
  username varchar(100) NOT NULL DEFAULT 'Anonymous',
  room int(11) NOT NULL,
  PRIMARY KEY (id),
  KEY room (room),
  CONSTRAINT users_ibfk_1 FOREIGN KEY (room) REFERENCES rooms (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8