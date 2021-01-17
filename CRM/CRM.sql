-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

-- -----------------------------------------------------
-- Schema CRM-db
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema CRM-db
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `CRM-db` DEFAULT CHARACTER SET utf8 ;
USE `CRM-db` ;

-- -----------------------------------------------------
-- Table `CRM-db`.`Utente`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `CRM-db`.`Utente` ;

CREATE TABLE IF NOT EXISTS `CRM-db`.`Utente` (
  `matricola` VARCHAR(6) NOT NULL,
  `nome` VARCHAR(20) NOT NULL,
  `cognome` VARCHAR(20) NOT NULL,
  `password` CHAR(32) NOT NULL,
  `ruolo` ENUM('manager', 'settorecommerciale', 'funzionario') NOT NULL,
  PRIMARY KEY (`matricola`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `CRM-db`.`Sede`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `CRM-db`.`Sede` ;

CREATE TABLE IF NOT EXISTS `CRM-db`.`Sede` (
  `via` VARCHAR(45) NOT NULL,
  `civico` VARCHAR(5) NOT NULL,
  `citta` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`via`, `civico`, `citta`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `CRM-db`.`PropostaCommerciale`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `CRM-db`.`PropostaCommerciale` ;

CREATE TABLE IF NOT EXISTS `CRM-db`.`PropostaCommerciale` (
  `codice` VARCHAR(10) NOT NULL,
  `descrizione` VARCHAR(45) NOT NULL,
  `terminata` DATE NULL,
  PRIMARY KEY (`codice`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `CRM-db`.`SalaRiunione`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `CRM-db`.`SalaRiunione` ;

CREATE TABLE IF NOT EXISTS `CRM-db`.`SalaRiunione` (
  `numero` INT NOT NULL,
  `Sede_via` VARCHAR(45) NOT NULL,
  `Sede_civico` VARCHAR(5) NOT NULL,
  `Sede_citta` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`numero`, `Sede_via`, `Sede_civico`, `Sede_citta`),
  INDEX `SalaRiunione_FK_Sede_idx` (`Sede_via` ASC, `Sede_civico` ASC, `Sede_citta` ASC),
  CONSTRAINT `fk_SalaRiunione_Sede`
    FOREIGN KEY (`Sede_via` , `Sede_civico` , `Sede_citta`)
    REFERENCES `CRM-db`.`Sede` (`via` , `civico` , `citta`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `CRM-db`.`Cliente`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `CRM-db`.`Cliente` ;

CREATE TABLE IF NOT EXISTS `CRM-db`.`Cliente` (
  `cf` VARCHAR(16) NOT NULL,
  `nome` VARCHAR(45) NOT NULL,
  `cognome` VARCHAR(45) NOT NULL,
  `nascita` DATE NOT NULL,
  `registrazione` DATE NOT NULL,
  `Funzionario_matricola` VARCHAR(6) NOT NULL,
  PRIMARY KEY (`cf`),
  INDEX `Cliente_FK_Funzionario_idx` (`Funzionario_matricola` ASC),
  CONSTRAINT `fk_Cliente_Funzionario1`
    FOREIGN KEY (`Funzionario_matricola`)
    REFERENCES `CRM-db`.`Utente` (`matricola`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `CRM-db`.`Accettata`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `CRM-db`.`Accettata` ;

CREATE TABLE IF NOT EXISTS `CRM-db`.`Accettata` (
  `proposta_commerciale` VARCHAR(10) NOT NULL,
  `cliente` VARCHAR(16) NOT NULL,
  PRIMARY KEY (`proposta_commerciale`, `cliente`),
  INDEX `Accettata_FK_Cliente_idx` (`cliente` ASC),
  INDEX `Accettata_FK_Codice_idx` (`proposta_commerciale` ASC),
  CONSTRAINT `fk_PropostaCommerciale_has_Cliente_PropostaCommerciale1`
    FOREIGN KEY (`proposta_commerciale`)
    REFERENCES `CRM-db`.`PropostaCommerciale` (`codice`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_PropostaCommerciale_has_Cliente_Cliente1`
    FOREIGN KEY (`cliente`)
    REFERENCES `CRM-db`.`Cliente` (`cf`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `CRM-db`.`Telefono`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `CRM-db`.`Telefono` ;

CREATE TABLE IF NOT EXISTS `CRM-db`.`Telefono` (
  `Cliente_cf` VARCHAR(16) NOT NULL,
  `numero` INT NOT NULL,
  PRIMARY KEY (`Cliente_cf`, `numero`),
  CONSTRAINT `fk_Telefono_Cliente1`
    FOREIGN KEY (`Cliente_cf`)
    REFERENCES `CRM-db`.`Cliente` (`cf`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `CRM-db`.`Mail`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `CRM-db`.`Mail` ;

CREATE TABLE IF NOT EXISTS `CRM-db`.`Mail` (
  `Cliente_cf` VARCHAR(16) NOT NULL,
  `mail` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`Cliente_cf`, `mail`),
  CONSTRAINT `fk_Mail_Cliente1`
    FOREIGN KEY (`Cliente_cf`)
    REFERENCES `CRM-db`.`Cliente` (`cf`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `CRM-db`.`Indirizzo`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `CRM-db`.`Indirizzo` ;

CREATE TABLE IF NOT EXISTS `CRM-db`.`Indirizzo` (
  `Cliente_cf` VARCHAR(16) NOT NULL,
  `via` VARCHAR(45) NOT NULL,
  `civico` VARCHAR(5) NOT NULL,
  `citta` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`Cliente_cf`, `via`, `civico`, `citta`),
  CONSTRAINT `fk_Indirizzo_Cliente1`
    FOREIGN KEY (`Cliente_cf`)
    REFERENCES `CRM-db`.`Cliente` (`cf`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `CRM-db`.`Fax`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `CRM-db`.`Fax` ;

CREATE TABLE IF NOT EXISTS `CRM-db`.`Fax` (
  `Cliente_cf` VARCHAR(16) NOT NULL,
  `fax` INT NOT NULL,
  PRIMARY KEY (`Cliente_cf`, `fax`),
  CONSTRAINT `fk_Fax_Cliente1`
    FOREIGN KEY (`Cliente_cf`)
    REFERENCES `CRM-db`.`Cliente` (`cf`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `CRM-db`.`Interazione`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `CRM-db`.`Interazione` ;

CREATE TABLE IF NOT EXISTS `CRM-db`.`Interazione` (
  `Cliente_cf` VARCHAR(16) NOT NULL,
  `data` DATETIME NOT NULL,
  `nota` VARCHAR(128) NOT NULL,
  PRIMARY KEY (`Cliente_cf`, `data`),
  CONSTRAINT `fk_Interazione_Cliente1`
    FOREIGN KEY (`Cliente_cf`)
    REFERENCES `CRM-db`.`Cliente` (`cf`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `CRM-db`.`Appuntamento`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `CRM-db`.`Appuntamento` ;

CREATE TABLE IF NOT EXISTS `CRM-db`.`Appuntamento` (
  `Cliente_cf` VARCHAR(16) NOT NULL,
  `SalaRiunione_numero` INT NOT NULL,
  `SalaRiunione_sede_via` VARCHAR(45) NOT NULL,
  `SalaRiunione_sede_civico` VARCHAR(5) NOT NULL,
  `SalaRiunione_sede_citta` VARCHAR(45) NOT NULL,
  `data` DATE NOT NULL,
  `ora_inizio` TIME NOT NULL,
  `ora_fine` TIME NOT NULL,
  `PropostaCommerciale_codice` VARCHAR(10) NOT NULL,
  INDEX `Appuntamento_FK_Cliente_idx` (`Cliente_cf` ASC),
  PRIMARY KEY (`SalaRiunione_numero`, `SalaRiunione_sede_via`, `SalaRiunione_sede_civico`, `SalaRiunione_sede_citta`, `data`, `ora_inizio`),
  INDEX `Appuntamento_FK_Codice_idx` (`PropostaCommerciale_codice` ASC),
  CONSTRAINT `fk_Appuntamento_Cliente1`
    FOREIGN KEY (`Cliente_cf`)
    REFERENCES `CRM-db`.`Cliente` (`cf`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Appuntamento_SalaRiunione1`
    FOREIGN KEY (`SalaRiunione_numero` , `SalaRiunione_sede_via` , `SalaRiunione_sede_civico` , `SalaRiunione_sede_citta`)
    REFERENCES `CRM-db`.`SalaRiunione` (`numero` , `Sede_via` , `Sede_civico` , `Sede_citta`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_Appuntamento_PropostaCommerciale1`
    FOREIGN KEY (`PropostaCommerciale_codice`)
    REFERENCES `CRM-db`.`PropostaCommerciale` (`codice`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `CRM-db`.`Societa`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `CRM-db`.`Societa` ;

CREATE TABLE IF NOT EXISTS `CRM-db`.`Societa` (
  `Cliente_cf` VARCHAR(16) NOT NULL,
  `ragione_sociale` VARCHAR(45) NOT NULL,
  `partita_iva` VARCHAR(16) NOT NULL,
  PRIMARY KEY (`Cliente_cf`),
  CONSTRAINT `fk_Società_Cliente1`
    FOREIGN KEY (`Cliente_cf`)
    REFERENCES `CRM-db`.`Cliente` (`cf`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;

USE `CRM-db` ;

-- -----------------------------------------------------
-- procedure login
-- -----------------------------------------------------

USE `CRM-db`;
DROP procedure IF EXISTS `CRM-db`.`login`;

DELIMITER $$
USE `CRM-db`$$
CREATE PROCEDURE `login` (in var_matricola varchar(6), in var_pass varchar(45), out var_role INT)
BEGIN
	declare var_user_role ENUM('manager', 'settorecommerciale', 'funzionario');
    
	select `ruolo` from `Utente`
		where `matricola` = var_matricola
        and `password` = md5(var_pass)
        into var_user_role;
        
        -- See the corresponding enum in the client
		if var_user_role = 'manager' then
			set var_role = 1;
		elseif var_user_role = 'settorecommerciale' then
			set var_role = 2;
		elseif var_user_role = 'funzionario' then
			set var_role = 3;
		else
			set var_role = 4;
		end if;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure aggiungi_funzionario
-- -----------------------------------------------------

USE `CRM-db`;
DROP procedure IF EXISTS `CRM-db`.`aggiungi_funzionario`;

DELIMITER $$
USE `CRM-db`$$
CREATE PROCEDURE `aggiungi_funzionario` (IN var_matricola VARCHAR(45), IN var_nome varchar(45), IN var_cognome VARCHAR(45), IN var_password VARCHAR(45))
BEGIN        
	insert into `Utente` values (var_matricola, var_nome, var_cognome, MD5(var_password), 'funzionario');
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure modifica_nota
-- -----------------------------------------------------

USE `CRM-db`;
DROP procedure IF EXISTS `CRM-db`.`modifica_nota`;

DELIMITER $$
USE `CRM-db`$$
CREATE PROCEDURE `modifica_nota` (in var_cf_cliente varchar(16), in var_data datetime, in var_nota varchar(128), in var_funzionario varchar(6))
BEGIN

	declare exit handler for sqlexception
    begin
		rollback;
        resignal;
	end;
    
    set transaction isolation level read committed; #evito letture sporche
    
	if (select Funzionario_matricola from Cliente where cf=var_cf_cliente)<>var_funzionario then
		signal sqlstate '45001' set message_text="Uncorrect customer";
    end if;
    if not exists(select * from `Interazione` where `Cliente_cf`= var_cf_cliente and `data`= var_data) then
		signal sqlstate '45001' set message_text="There is no note on the selected date";
	end if;
	update `Interazione` 
    set `nota`= var_nota 
    where `Cliente_cf`= var_cf_cliente and `data`= var_data;
    commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure aggiungi_nota
-- -----------------------------------------------------

USE `CRM-db`;
DROP procedure IF EXISTS `CRM-db`.`aggiungi_nota`;

DELIMITER $$
USE `CRM-db`$$
CREATE PROCEDURE `aggiungi_nota` (in var_cliente_cf varchar(16), in var_nota varchar(128), in var_funzionario varchar(6))
BEGIN
	declare var_date datetime;
    declare exit handler for sqlexception
    begin
		rollback;
        resignal;
	end;
    
    set transaction isolation level read committed; #evito letture sporche
    
	if (select Funzionario_matricola from Cliente where cf=var_cliente_CF)<>var_funzionario then
		signal sqlstate '45001' set message_text="Uncorrect customer";
    end if;
    set var_date =DATE_FORMAT(NOW(), '%Y/%m/%d %H/%i');
	insert into `Interazione` (`Cliente_CF`,`data`, `nota`) values (var_cliente_cf,var_date, var_nota);    
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure termina_proposta
-- -----------------------------------------------------

USE `CRM-db`;
DROP procedure IF EXISTS `CRM-db`.`termina_proposta`;

DELIMITER $$
USE `CRM-db`$$
CREATE PROCEDURE `termina_proposta` (in var_codice varchar(10))
BEGIN
	
	declare exit handler for sqlexception
    begin
		rollback;
        resignal;
	end; 
    
    set transaction isolation level read committed; #evito letture sporche
    
	if(select count(*) from `PropostaCommerciale` where `codice`= var_codice and terminata is null)=0 then
		signal sqlstate '45001' set message_text="Wrong proposal ID";
    end if;
	update `PropostaCommerciale` set `Terminata`=curdate() where `codice`= var_codice;     
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure elimina_nota
-- -----------------------------------------------------

USE `CRM-db`;
DROP procedure IF EXISTS `CRM-db`.`elimina_nota`;

DELIMITER $$
USE `CRM-db`$$
CREATE PROCEDURE `elimina_nota` (in var_cliente_CF varchar(16), in var_data datetime, in var_funzionario varchar(6))
BEGIN

	declare exit handler for sqlexception
    begin
		rollback;
        resignal;
	end;
    
    set transaction isolation level read committed; #evito letture sporche
    
	if (select Funzionario_matricola from Cliente where cf=var_cliente_CF)<>var_funzionario then
		signal sqlstate '45001' set message_text="Uncorrect customer";
    end if;
	DELETE FROM `Interazione` where  `Cliente_CF`= var_cliente_CF and `data`= var_data;
	commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure aggiungi_appuntamento
-- -----------------------------------------------------

USE `CRM-db`;
DROP procedure IF EXISTS `CRM-db`.`aggiungi_appuntamento`;

DELIMITER $$
USE `CRM-db`$$
CREATE PROCEDURE `aggiungi_appuntamento` (in var_CF varchar(16), in var_numero_sala int, in var_viasede varchar(45), in var_civicosede varchar(5), in var_cittasede varchar(45), in var_data date, in var_inizio time, in var_fine time, in var_codice varchar(10))
BEGIN
	declare exit handler for sqlexception
    begin
		rollback;
        resignal;
	end;
    
	if var_data<CURDATE() or (var_data=CURDATE() and var_inizio<CURTIME()) then
		signal sqlstate '45001' set message_text="Enter a date after the current date";
	end if;
	INSERT INTO `Appuntamento` VALUES(var_CF, var_numero_sala, var_viasede, var_civicosede, var_cittasede, var_data, var_inizio, var_fine, var_codice);
	commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure inserisci_cliente
-- -----------------------------------------------------

USE `CRM-db`;
DROP procedure IF EXISTS `CRM-db`.`inserisci_cliente`;

DELIMITER $$
USE `CRM-db`$$
CREATE PROCEDURE `inserisci_cliente` (in var_cf varchar(16), in nome varchar(45), in cognome varchar(45), in var_nascita date, in var_Funzionario_matricola varchar(6), in var_mail varchar(45), in var_telefono varchar(10), in var_via varchar(45), in var_civico varchar(45), in var_citta varchar(45), in var_fax varchar(11))
BEGIN
	
    #Transazione perché insert collegati tra loro

	INSERT INTO `Cliente` (cf, nome, cognome, nascita, Funzionario_matricola) 
	VALUES (var_cf, nome, cognome, var_nascita, var_Funzionario_matricola);
	INSERT INTO `Mail` (Cliente_cf, mail) 
	VALUES (var_cf, var_mail);
	INSERT INTO `Telefono` (Cliente_cf, numero) 
	VALUES (var_cf, var_telefono);
	INSERT INTO `Indirizzo` (Cliente_cf, via, civico, citta) 
	VALUES (var_cf, var_via, var_civico, var_citta);
	INSERT INTO `Fax` (Cliente_cf, fax) 
	VALUES (var_cf, var_fax);
	COMMIT;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure inserisci_societa
-- -----------------------------------------------------

USE `CRM-db`;
DROP procedure IF EXISTS `CRM-db`.`inserisci_societa`;

DELIMITER $$
USE `CRM-db`$$
CREATE PROCEDURE `inserisci_societa` (in var_cf varchar(16),in nome varchar(45), in cognome varchar(45), in var_nascita date, in var_Funzionario_matricola varchar(6), in var_mail varchar(45), in var_telefono varchar(10), in var_via varchar(45), in var_civico varchar(45), in var_citta varchar(45), in var_fax varchar(11), in var_ragione_sociale varchar(45), in var_partita_iva varchar(11))
BEGIN
	declare var_num int;
    
    declare exit handler for sqlexception
    begin
		rollback;
        resignal;
	end;
    
    set transaction isolation level read committed; #evito letture sporche
  
    select count(*) from Cliente where cf=var_cf into var_num;
    if var_num=0 then
		INSERT INTO `Cliente` (cf, nome, cognome, nascita, Funzionario_matricola) 
		VALUES (var_cf, nome, cognome, var_nascita, var_Funzionario_matricola);
		INSERT INTO `Mail` (Cliente_cf, mail) 
		VALUES (var_cf, var_mail);
		INSERT INTO `Telefono` (Cliente_cf, numero) 
		VALUES (var_cf, var_telefono);
		INSERT INTO `Indirizzo` (Cliente_cf, via, civico, citta) 
		VALUES (var_cf, var_via, var_civico, var_citta);
		INSERT INTO `Fax` (Cliente_cf, fax) 
		VALUES (var_cf, var_fax);
    	INSERT INTO `Societa` (Cliente_cf, ragione_sociale, partita_iva) VALUES (var_cf, var_ragione_sociale, var_partita_iva);
	else
		select count(*) from Societa where Cliente_cf=var_cf into var_num;
		if var_num=0 then
			INSERT INTO `Societa` (Cliente_cf, ragione_sociale, partita_iva) VALUES (var_cf, var_ragione_sociale, var_partita_iva);
		else
			signal sqlstate '45001' set message_text="The client is already registered in the CRM system";
		end if;
	end if;
    commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure inserisci_proposta
-- -----------------------------------------------------

USE `CRM-db`;
DROP procedure IF EXISTS `CRM-db`.`inserisci_proposta`;

DELIMITER $$
USE `CRM-db`$$
CREATE PROCEDURE `inserisci_proposta` (in var_codice varchar(10), in var_descrizione varchar(45))
BEGIN
	insert into `PropostaCommerciale` (codice, descrizione) values (var_codice, var_descrizione);
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure nuovi_appuntamenti
-- -----------------------------------------------------

USE `CRM-db`;
DROP procedure IF EXISTS `CRM-db`.`nuovi_appuntamenti`;

DELIMITER $$
USE `CRM-db`$$
CREATE PROCEDURE `nuovi_appuntamenti` (in var_matricola varchar(6))
BEGIN
	set transaction read only;
    set transaction isolation level read committed; #evito letture sporche
    
	select `a`.Cliente_cf, `a`.SalaRiunione_sede_citta as citta, `a`.SalaRiunione_sede_via as via, `a`.SalaRiunione_sede_civico as civico,`a`.SalaRiunione_numero as numero_sala, DATE_FORMAT(`data`, '%d/%m/%Y') as `data`, DATE_FORMAT(ora_inizio, '%H:%i') as ora_inizio, DATE_FORMAT(ora_fine, '%H:%i') as ora_fine, `a`.PropostaCommerciale_codice as codice 
    from `Appuntamento` as `a` join `Cliente` on Cliente_cf=cf
    where Cliente_cf in (select cf from `Cliente` where Funzionario_matricola=var_matricola) and (DATE_FORMAT(`data`, '%Y/%m/%d')>CURDATE() or (DATE_FORMAT(`data`, '%Y/%m/%d')=CURDATE() and ora_inizio>=CURTIME()))
	order by DATE_FORMAT(`data`, '%Y/%m/%d'),`ora_inizio`, `SalaRiunione_numero`;
    commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure inserisci_proposta_accettata
-- -----------------------------------------------------

USE `CRM-db`;
DROP procedure IF EXISTS `CRM-db`.`inserisci_proposta_accettata`;

DELIMITER $$
USE `CRM-db`$$
CREATE PROCEDURE `inserisci_proposta_accettata` (in var_codice_proposta varchar(10), in var_cf_cliente varchar(16), in matricola varchar(6))
BEGIN
	 declare var_matricola varchar(6);
    declare exit handler for sqlexception
    begin
		rollback;
        resignal;
	end;
		
    set transaction isolation level read committed;
    
    select Funzionario_matricola into var_matricola from Cliente where cf=var_cf_cliente;
    if matricola<>var_matricola then
		signal sqlstate '45001' set message_text="Selected customer isn't your";
    end if;
	INSERT INTO `CRM-db`.`Accettata` VALUES (var_codice_proposta, var_cf_cliente);
	commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure visualizza_lista_clienti
-- -----------------------------------------------------

USE `CRM-db`;
DROP procedure IF EXISTS `CRM-db`.`visualizza_lista_clienti`;

DELIMITER $$
USE `CRM-db`$$
CREATE PROCEDURE `visualizza_lista_clienti` (in var_funzionario varchar(6))
BEGIN
	
    set transaction read only;
    set transaction isolation level read committed; #evito letture sporche
    
	select `c`.CF, `c`.nome, `c`.cognome
    from Cliente as c 
    where `Funzionario_matricola`=var_funzionario;
    commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure aggiungi_mail
-- -----------------------------------------------------

USE `CRM-db`;
DROP procedure IF EXISTS `CRM-db`.`aggiungi_mail`;

DELIMITER $$
USE `CRM-db`$$
CREATE PROCEDURE `aggiungi_mail` (in var_cf varchar(16), in var_mail varchar(45))
BEGIN
	insert into Mail (Cliente_cf, mail) values (var_cf, var_mail);
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure aggiungi_telefono
-- -----------------------------------------------------

USE `CRM-db`;
DROP procedure IF EXISTS `CRM-db`.`aggiungi_telefono`;

DELIMITER $$
USE `CRM-db`$$
CREATE PROCEDURE `aggiungi_telefono` (in var_cf varchar(16), in var_numero varchar(10))
BEGIN
	insert into Telefono (Cliente_cf, numero) values (var_cf, var_numero);
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure aggiungi_fax
-- -----------------------------------------------------

USE `CRM-db`;
DROP procedure IF EXISTS `CRM-db`.`aggiungi_fax`;

DELIMITER $$
USE `CRM-db`$$
CREATE PROCEDURE `aggiungi_fax` (in var_cf varchar(16), in var_numero varchar(11))
BEGIN
	insert into Fax (Cliente_cf, numero) values (var_cf, var_numero);
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure visualizza_societa
-- -----------------------------------------------------

USE `CRM-db`;
DROP procedure IF EXISTS `CRM-db`.`visualizza_societa`;

DELIMITER $$
USE `CRM-db`$$
CREATE PROCEDURE `visualizza_societa` (in var_cf varchar(16), in matricola varchar(6))
BEGIN
	declare var_num int;
	
    declare var_matricola varchar(6);
    declare exit handler for sqlexception
    begin
		rollback;
        resignal;
	end;
	
    set transaction read only;
    set transaction isolation level read committed; #evito letture sporche, controllo prima che il funzionario che vuole
    #visualizzare il cliente è quello che lo ha in gestione e poi controllo se il cliente selezionato è referente di una società.
    
    select Funzionario_matricola into var_matricola from Cliente where cf=var_cf;
    if matricola<>var_matricola then
		signal sqlstate '45001' set message_text="Selected customer isn't your";
    end if;
    
	select count(*) from Societa where Cliente_cf=var_cf into var_num;
	if var_num>0 then
		select ragione_sociale, partita_iva from Societa where Cliente_cf=var_cf;
    end if;
    commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure visualizza_mail
-- -----------------------------------------------------

USE `CRM-db`;
DROP procedure IF EXISTS `CRM-db`.`visualizza_mail`;

DELIMITER $$
USE `CRM-db`$$
CREATE PROCEDURE `visualizza_mail` (in var_cf varchar(16), in matricola varchar(6))
BEGIN
	 declare var_matricola varchar(6);
    declare exit handler for sqlexception
    begin
		rollback;
        resignal;
	end;
		
	set transaction read only;
    set transaction isolation level read committed; #evito letture sporche
    
    select Funzionario_matricola into var_matricola from Cliente where cf=var_cf;
    if matricola<>var_matricola then
		signal sqlstate '45001' set message_text="Selected customer isn't your";
    end if;
    
	select mail from Mail where Cliente_cf=var_cf;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure visualizza_fax
-- -----------------------------------------------------

USE `CRM-db`;
DROP procedure IF EXISTS `CRM-db`.`visualizza_fax`;

DELIMITER $$
USE `CRM-db`$$
CREATE PROCEDURE `visualizza_fax` (in var_cf varchar(16), in matricola varchar(6))
BEGIN
	declare var_num int;
	declare var_matricola varchar(6);
    declare exit handler for sqlexception
    begin
		rollback;
        resignal;
	end;
		
    set transaction read only;
	set transaction isolation level read committed; #evito letture sporche
    
    select Funzionario_matricola into var_matricola from Cliente where cf=var_cf;
    if matricola<>var_matricola then
		signal sqlstate '45001' set message_text="Selected customer isn't your";
    end if;
    
	select count(*) from Fax where Cliente_cf=var_cf into var_num;
	if var_num>0 then
		select fax from Fax where Cliente_cf=var_cf;
    end if;
    commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure visualizza_indirizzo
-- -----------------------------------------------------

USE `CRM-db`;
DROP procedure IF EXISTS `CRM-db`.`visualizza_indirizzo`;

DELIMITER $$
USE `CRM-db`$$
CREATE PROCEDURE `visualizza_indirizzo` (in var_cf varchar(16), in matricola varchar(6))
BEGIN
	declare var_matricola varchar(6);
    declare exit handler for sqlexception
    begin
		rollback;
        resignal;
	end;
		
	set transaction read only;
    set transaction isolation level read committed;
    
    select Funzionario_matricola into var_matricola from Cliente where cf=var_cf;
    if matricola<>var_matricola then
		signal sqlstate '45001' set message_text="Selected customer isn't your";
    end if;
	select via, civico, citta from Indirizzo where Cliente_cf=var_cf;
	commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure visualizza_telefono
-- -----------------------------------------------------

USE `CRM-db`;
DROP procedure IF EXISTS `CRM-db`.`visualizza_telefono`;

DELIMITER $$
USE `CRM-db`$$
CREATE PROCEDURE `visualizza_telefono` (in var_cf varchar(16), in matricola varchar(6))
BEGIN
	 declare var_matricola varchar(6);
    declare exit handler for sqlexception
    begin
		rollback;
        resignal;
	end;
		
    set transaction isolation level read committed;
    
    select Funzionario_matricola into var_matricola from Cliente where cf=var_cf;
    if matricola<>var_matricola then
		signal sqlstate '45001' set message_text="Selected customer isn't your";
    end if;
    
	set transaction read only;
    set transaction isolation level read committed; #evito letture sporche
	select numero as telefono from Telefono where Cliente_cf=var_cf;
	commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure visualizza_accettate
-- -----------------------------------------------------

USE `CRM-db`;
DROP procedure IF EXISTS `CRM-db`.`visualizza_accettate`;

DELIMITER $$
USE `CRM-db`$$
CREATE PROCEDURE `visualizza_accettate` (in var_cf varchar(16), in matricola varchar(6))
BEGIN
	declare var_num int;
	 declare var_matricola varchar(6);
    declare exit handler for sqlexception
    begin
		rollback;
        resignal;
	end;
	
    set transaction read only;
    set transaction isolation level read committed; #evito letture sporche
    
    select Funzionario_matricola into var_matricola from Cliente where cf=var_cf;
    if matricola<>var_matricola then
		signal sqlstate '45001' set message_text="Selected customer isn't your";
    end if;
	select count(*) from Accettata where cliente=var_cf into var_num;
    if var_num>0 then
		select codice, descrizione from Accettata join PropostaCommerciale on proposta_commerciale=codice where cliente=var_cf;
	end if;
    commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure visualizza_note
-- -----------------------------------------------------

USE `CRM-db`;
DROP procedure IF EXISTS `CRM-db`.`visualizza_note`;

DELIMITER $$
USE `CRM-db`$$
CREATE PROCEDURE `visualizza_note` (in var_cf varchar(16), in matricola varchar(6))
BEGIN
	declare var_num int;
    declare var_matricola varchar(6);
    declare exit handler for sqlexception
    begin
		rollback;
        resignal;
	end;
		
	set transaction read only;
    set transaction isolation level read committed; #evito letture sporche 
    
    select Funzionario_matricola into var_matricola from Cliente where cf=var_cf;
    if matricola<>var_matricola then
		signal sqlstate '45001' set message_text="Selected customer isn't your";
    end if;
    if (select count(*) from Cliente where cf=var_cf)=0 then
		signal sqlstate '45001' set message_text="There is no customer with this tax code";
    end if;
    
	select count(*) from Interazione where Cliente_cf=var_cf into var_num;
    if var_num>0 then
		select DATE_FORMAT(`data`, '%d/%m/%Y %H:%i') as `data`, nota from Interazione where Cliente_cf=var_cf;
	else
		signal sqlstate '45002' set message_text="There aren't note for this customer";
    end if;
    commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure proposte_attive
-- -----------------------------------------------------

USE `CRM-db`;
DROP procedure IF EXISTS `CRM-db`.`proposte_attive`;

DELIMITER $$
USE `CRM-db`$$
CREATE PROCEDURE `proposte_attive` ()
BEGIN
	set transaction read only;
    set transaction isolation level read committed;#evito letture sporche
	select codice, descrizione
    from PropostaCommerciale
    where terminata is null;
    commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure visualizza_cliente
-- -----------------------------------------------------

USE `CRM-db`;
DROP procedure IF EXISTS `CRM-db`.`visualizza_cliente`;

DELIMITER $$
USE `CRM-db`$$
CREATE PROCEDURE `visualizza_cliente` (in var_cf varchar(16), in matricola varchar(6))
BEGIN
	 declare var_matricola varchar(6);
    declare exit handler for sqlexception
    begin
		rollback;
        resignal;
	end;
	
	
	set transaction read only;
    set transaction isolation level read committed; #evito letture sporche
    
    select Funzionario_matricola into var_matricola from Cliente where cf=var_cf;
    if matricola<>var_matricola then
		signal sqlstate '45001' set message_text="Selected customer isn't your";
    end if;
	select nome, cognome, DATE_FORMAT(nascita, '%d/%m/%Y') as nascita, DATE_FORMAT(registrazione,'%d/%m/%Y') as registrazione from Cliente where cf=var_cf;
	commit;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure visualizza_sale
-- -----------------------------------------------------

USE `CRM-db`;
DROP procedure IF EXISTS `CRM-db`.`visualizza_sale`;

DELIMITER $$
USE `CRM-db`$$
CREATE PROCEDURE `visualizza_sale` (in var_citta varchar(45))
BEGIN
	declare var_count int;
    
    declare exit handler for sqlexception
    begin
		rollback;
        resignal;
	end;
    set transaction read only;
    set transaction isolation level read committed; #evito letture sporche
    
    select count(*) 
    from Appuntamento
    where SalaRiunione_sede_citta=var_citta and `data`>=NOW()
    into var_count;
    if var_count=0 then
		signal sqlstate '45002' set message_text="There are no busy meeting rooms in the selected city";
    end if;
	select SalaRiunione_numero as numero_sala, SalaRiunione_sede_civico as civico_sede, SalaRiunione_sede_via as via_sede, SalaRiunione_sede_citta as citta_sede, DATE_FORMAT(`data`, '%d/%m/%Y') as `data`, DATE_FORMAT(ora_inizio, '%H:%i') as ora_inizio, DATE_FORMAT(ora_fine, '%H:%i') as ora_fine
    from Appuntamento
    where SalaRiunione_sede_citta=var_citta and (`data`>CURDATE() or (`data`=CURDATE() and ora_inizio>CURTIME())
	order by DATE_FORMAT(`data`, '%Y/%m/%d'),`ora_inizio`, `SalaRiunione_numero`;
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure aggiungi_indirizzo
-- -----------------------------------------------------

USE `CRM-db`;
DROP procedure IF EXISTS `CRM-db`.`aggiungi_indirizzo`;

DELIMITER $$
USE `CRM-db`$$
CREATE PROCEDURE `aggiungi_indirizzo` (in var_cf varchar(16), in var_via varchar(45), in var_civico varchar(5), in var_citta varchar(46))
BEGIN
	INSERT INTO `CRM-db`.`Indirizzo` (`Cliente_cf`, `via`, `civico`, `citta`) VALUES (var_cf, var_via, var_civico, var_citta);
END$$

DELIMITER ;

-- -----------------------------------------------------
-- procedure tutti_appuntamenti
-- -----------------------------------------------------

USE `CRM-db`;
DROP procedure IF EXISTS `CRM-db`.`tutti_appuntamenti`;

DELIMITER $$
USE `CRM-db`$$
CREATE PROCEDURE `tutti_appuntamenti` (in var_matricola varchar(6))
BEGIN
	set transaction read only;
    set transaction isolation level read committed; #evito letture sporche
    
	select `a`.Cliente_cf, `a`.SalaRiunione_sede_citta as citta, `a`.SalaRiunione_sede_via as via, `a`.SalaRiunione_sede_civico as civico,`a`.SalaRiunione_numero as numero_sala, DATE_FORMAT(`data`, '%d/%m/%Y') as `data`, DATE_FORMAT(ora_inizio, '%H:%i') as ora_inizio, DATE_FORMAT(ora_fine, '%H:%i') as ora_fine, `a`.PropostaCommerciale_codice as codice 
    from `Appuntamento` as `a` join `Cliente` on Cliente_cf=cf
    where Cliente_cf in (select cf from `Cliente` where Funzionario_matricola=var_matricola)
	order by DATE_FORMAT(`data`, '%Y/%m/%d'),`ora_inizio`, `SalaRiunione_numero`;
    commit;
END$$

DELIMITER ;
SET SQL_MODE = '';
GRANT USAGE ON *.* TO funzionario;
 DROP USER funzionario;
SET SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';
CREATE USER 'funzionario' IDENTIFIED BY 'funzionario';

GRANT EXECUTE ON procedure `CRM-db`.`modifica_nota` TO 'funzionario';
GRANT EXECUTE ON procedure `CRM-db`.`visualizza_lista_clienti` TO 'funzionario';
GRANT EXECUTE ON procedure `CRM-db`.`nuovi_appuntamenti` TO 'funzionario';
GRANT EXECUTE ON procedure `CRM-db`.`inserisci_proposta_accettata` TO 'funzionario';
GRANT EXECUTE ON procedure `CRM-db`.`elimina_nota` TO 'funzionario';
GRANT EXECUTE ON procedure `CRM-db`.`aggiungi_nota` TO 'funzionario';
GRANT EXECUTE ON procedure `CRM-db`.`aggiungi_appuntamento` TO 'funzionario';
GRANT EXECUTE ON procedure `CRM-db`.`visualizza_note` TO 'funzionario';
GRANT EXECUTE ON procedure `CRM-db`.`visualizza_fax` TO 'funzionario';
GRANT EXECUTE ON procedure `CRM-db`.`visualizza_indirizzo` TO 'funzionario';
GRANT EXECUTE ON procedure `CRM-db`.`visualizza_mail` TO 'funzionario';
GRANT EXECUTE ON procedure `CRM-db`.`visualizza_accettate` TO 'funzionario';
GRANT EXECUTE ON procedure `CRM-db`.`visualizza_societa` TO 'funzionario';
GRANT EXECUTE ON procedure `CRM-db`.`visualizza_telefono` TO 'funzionario';
GRANT EXECUTE ON procedure `CRM-db`.`proposte_attive` TO 'funzionario';
GRANT EXECUTE ON procedure `CRM-db`.`visualizza_cliente` TO 'funzionario';
GRANT EXECUTE ON procedure `CRM-db`.`visualizza_sale` TO 'funzionario';
GRANT SELECT, INSERT ON TABLE `CRM-db`.`Accettata` TO 'funzionario';
GRANT EXECUTE ON procedure `CRM-db`.`tutti_appuntamenti` TO 'funzionario';
GRANT SELECT ON TABLE `CRM-db`.`Cliente` TO 'funzionario';
GRANT SELECT ON TABLE `CRM-db`.`Fax` TO 'funzionario';
GRANT SELECT ON TABLE `CRM-db`.`Indirizzo` TO 'funzionario';
GRANT INSERT, SELECT, UPDATE ON TABLE `CRM-db`.`Interazione` TO 'funzionario';
GRANT SELECT ON TABLE `CRM-db`.`Mail` TO 'funzionario';
GRANT SELECT ON TABLE `CRM-db`.`PropostaCommerciale` TO 'funzionario';
GRANT SELECT ON TABLE `CRM-db`.`SalaRiunione` TO 'funzionario';
GRANT SELECT ON TABLE `CRM-db`.`Sede` TO 'funzionario';
GRANT SELECT ON TABLE `CRM-db`.`Societa` TO 'funzionario';
GRANT SELECT ON TABLE `CRM-db`.`Telefono` TO 'funzionario';
SET SQL_MODE = '';
GRANT USAGE ON *.* TO commerciale;
 DROP USER commerciale;
SET SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';
CREATE USER 'commerciale' IDENTIFIED BY 'commerciale';

GRANT EXECUTE ON procedure `CRM-db`.`inserisci_cliente` TO 'commerciale';
GRANT EXECUTE ON procedure `CRM-db`.`aggiungi_mail` TO 'commerciale';
GRANT EXECUTE ON procedure `CRM-db`.`inserisci_societa` TO 'commerciale';
GRANT EXECUTE ON procedure `CRM-db`.`aggiungi_fax` TO 'commerciale';
GRANT EXECUTE ON procedure `CRM-db`.`aggiungi_telefono` TO 'commerciale';
GRANT EXECUTE ON procedure `CRM-db`.`aggiungi_indirizzo` TO 'commerciale';
GRANT INSERT, SELECT ON TABLE `CRM-db`.`Cliente` TO 'commerciale';
GRANT SELECT, INSERT ON TABLE `CRM-db`.`Fax` TO 'commerciale';
GRANT SELECT, INSERT ON TABLE `CRM-db`.`Indirizzo` TO 'commerciale';
GRANT INSERT ON TABLE `CRM-db`.`Mail` TO 'commerciale';
GRANT INSERT, SELECT ON TABLE `CRM-db`.`Societa` TO 'commerciale';
GRANT INSERT ON TABLE `CRM-db`.`Telefono` TO 'commerciale';
SET SQL_MODE = '';
GRANT USAGE ON *.* TO manager;
 DROP USER manager;
SET SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';
CREATE USER 'manager' IDENTIFIED BY 'manager';

GRANT EXECUTE ON procedure `CRM-db`.`aggiungi_funzionario` TO 'manager';
GRANT EXECUTE ON procedure `CRM-db`.`termina_proposta` TO 'manager';
GRANT EXECUTE ON procedure `CRM-db`.`inserisci_proposta` TO 'manager';
GRANT EXECUTE ON procedure `CRM-db`.`proposte_attive` TO 'manager';
GRANT INSERT ON TABLE `CRM-db`.`Utente` TO 'manager';
GRANT SELECT, UPDATE, INSERT ON TABLE `CRM-db`.`PropostaCommerciale` TO 'manager';
SET SQL_MODE = '';
GRANT USAGE ON *.* TO login;
 DROP USER login;
SET SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';
CREATE USER 'login' IDENTIFIED BY 'login';

GRANT EXECUTE ON procedure `CRM-db`.`login` TO 'login';
GRANT SELECT ON TABLE `CRM-db`.`Utente` TO 'login';

SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
USE `CRM-db`;

DELIMITER $$

USE `CRM-db`$$
DROP TRIGGER IF EXISTS `CRM-db`.`Cliente_BEFORE_INSERT` $$
USE `CRM-db`$$
CREATE DEFINER = CURRENT_USER TRIGGER `CRM-db`.`Cliente_BEFORE_INSERT` BEFORE INSERT ON `Cliente` FOR EACH ROW
BEGIN
	set new.registrazione = curdate();
    
    if not (YEAR(NOW())-YEAR(new.nascita))>18 OR (DAY(NOW())>DAY(new.nascita) AND MONTH(NOW())>=MONTH(new.nascita) AND YEAR(NOW())-YEAR(new.nascita)=18) then
		signal sqlstate '45001' set message_text="Customer is a minor";
	end if;
    
    if new.cf not regexp'^[A-Z]{6}[0-9]{2}[A-Z][0-9]{2}[A-Z][0-9]{3}[A-Z]$' then
		signal sqlstate '45001' set message_text="Incorrect tax code";
    end if;
END$$


USE `CRM-db`$$
DROP TRIGGER IF EXISTS `CRM-db`.`Accettata_BEFORE_INSERT` $$
USE `CRM-db`$$
CREATE DEFINER = CURRENT_USER TRIGGER `CRM-db`.`Accettata_BEFORE_INSERT` BEFORE INSERT ON `Accettata` FOR EACH ROW
BEGIN    
	if (select `terminata` from `PropostaCommerciale` where `codice`=NEW.proposta_commerciale) is not null then
		signal sqlstate '45000';
	end if;
END$$


USE `CRM-db`$$
DROP TRIGGER IF EXISTS `CRM-db`.`Mail_BEFORE_INSERT` $$
USE `CRM-db`$$
CREATE DEFINER = CURRENT_USER TRIGGER `CRM-db`.`Mail_BEFORE_INSERT` BEFORE INSERT ON `Mail` FOR EACH ROW
BEGIN
	if new.mail not regexp'^[a-zA-Z0-9][a-zA-Z0-9._-]*[a-zA-Z0-9._-]@[a-zA-Z0-9][a-zA-Z0-9._-]*[a-zA-Z0-9]\\.[a-zA-Z]{2,63}$' then
		signal sqlstate '45001' set message_text="Incorrect mail";
    end if;
END$$


USE `CRM-db`$$
DROP TRIGGER IF EXISTS `CRM-db`.`Appuntamento_BEFORE_INSERT` $$
USE `CRM-db`$$
CREATE DEFINER = CURRENT_USER TRIGGER `CRM-db`.`Appuntamento_BEFORE_INSERT` BEFORE INSERT ON `Appuntamento` FOR EACH ROW
BEGIN
    declare var_matricola varchar(6);
    select Funzionario_matricola into var_matricola from Cliente where cf=new.Cliente_cf;
	if exists(select * from PropostaCommerciale where new.PropostaCommerciale_codice=codice and terminata is not null) then
		signal sqlstate '45001' set message_text="Proposta commerciale terminata";
    end if;
    
    if exists(select * from Appuntamento where `data`=new.`data` and new.ora_inizio>=ora_inizio and new.ora_inizio<ora_fine and new.Cliente_cf in(select cf from Cliente where Funzionario_matricola=var_matricola)) then
		signal sqlstate '45001' set message_text="You have another appoinment at the same time";
	end if;

    
	if exists(select * from Appuntamento where `data`=new.`data` and new.ora_fine>ora_inizio and new.ora_fine<=ora_fine and new.Cliente_cf in(select cf from Cliente where Funzionario_matricola=var_matricola)) then
		signal sqlstate '45001' set message_text="You have another appointment at the same time";
	end if;
    
    if exists(select * from Appuntamento where SalaRiunione_numero=new.SalaRiunione_numero and SalaRiunione_sede_via=new.SalaRiunione_sede_via and SalaRiunione_sede_civico=new.SalaRiunione_sede_civico and SalaRiunione_sede_citta=new.SalaRiunione_sede_citta and `data`=new.`data` and new.ora_inizio>ora_inizio and new.ora_inizio<ora_fine) then
		signal sqlstate '45001' set message_text="There is another appoinment in the same data and in the same meeting room";
	end if;

	if exists(select * from Appuntamento where SalaRiunione_numero=new.SalaRiunione_numero and SalaRiunione_sede_via=new.SalaRiunione_sede_via and SalaRiunione_sede_civico=new.SalaRiunione_sede_civico and SalaRiunione_sede_citta=new.SalaRiunione_sede_citta and `data`=new.`data` and new.ora_fine>ora_inizio and new.ora_fine<=ora_fine) then
		signal sqlstate '45001' set message_text="There is another appoinment in the same data and in the same meeting room";
	end if;
    
    if new.ora_inizio>new.ora_fine then
		signal sqlstate '45001' set message_text="ending time must be later than starting time";
	end if;
    
END$$


DELIMITER ;
