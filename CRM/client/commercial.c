#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"

static void register_company(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[15];

	// Input for the registration routine
	char cf[17];
	char nome[46]; 
	char cognome[46]; 
	char matricola[7];
	char giorno[3];
	char mese[3];
	char anno[5];
	char mail[46]; 
	char telefono[11]; 
	char fax[12];
	char via[46];
	char civico[6];
	char citta[46];
	char ragione_sociale[46];
	char partita_iva[12];
	MYSQL_TIME nascita;
	memset(&nascita,0, sizeof(nascita));
	int numerot, numerof;

	// Get the required information
	printf("\nTax code: ");
	getInput(17, cf, false);
	printf("Name: ");
	getInput(46, nome, false);
	printf("Surname: ");
	getInput(46, cognome, false);
	printf("Officer ID: ");
	getInput(7, matricola, false);
	printf("Date of birth:\n");
	printf("Day: ");
	getInput(3, giorno, false);
	printf("Month: ");
	getInput(3, mese, false);
	printf("Year: ");
	getInput(5, anno, false);
	printf("Mail: ");
	getInput(46, mail, false);
	printf("Telephone: ");
	getInput(11, telefono, false);
	printf("Fax: ");
	getInput(12, fax, false);
	printf("Address:\n");
	printf("Street: ");
	getInput(46, via, false);
	printf("Street number: ");
	getInput(6, civico, false);
	printf("City: ");
	getInput(46, citta, false);
	printf("Legal company mail: ");
	getInput(46, ragione_sociale, false);
	printf("VAT number: ");
	getInput(46, partita_iva, false);

	nascita.day=atoi(giorno);
	nascita.month=atoi(mese);
	nascita.year=atoi(anno);
	numerot=atoi(telefono);
	numerof=atoi(fax);

	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call inserisci_societa(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?,?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize register company statement\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[0].buffer = cf;
	param[0].buffer_length = strlen(cf);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[1].buffer = nome;
	param[1].buffer_length = strlen(nome);

	param[2].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[2].buffer = cognome;
	param[2].buffer_length = strlen(cognome);

	param[3].buffer_type = MYSQL_TYPE_DATE; 		
	param[3].buffer = &nascita;
	param[3].buffer_length = sizeof(nascita);

	param[4].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[4].buffer = matricola;
	param[4].buffer_length = strlen(matricola);

	param[5].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[5].buffer = mail;
	param[5].buffer_length = strlen(mail);

	param[6].buffer_type = MYSQL_TYPE_LONG;
	param[6].buffer = &numerot;
	param[6].buffer_length = sizeof(numerot);

	param[7].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[7].buffer = via;
	param[7].buffer_length = strlen(via);

	param[8].buffer_type = MYSQL_TYPE_VAR_STRING; 		
	param[8].buffer = civico;
	param[8].buffer_length = strlen(civico);

	param[9].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[9].buffer = citta;
	param[9].buffer_length = strlen(citta);

	param[10].buffer_type = MYSQL_TYPE_LONG;
	param[10].buffer = &numerof;
	param[10].buffer_length = sizeof(numerof);

	param[11].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[11].buffer = ragione_sociale;
	param[11].buffer_length = strlen(ragione_sociale);

	param[12].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[12].buffer = partita_iva;
	param[12].buffer_length = strlen(partita_iva);	

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for register company\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "An error occurred while registering company.");
	} else{
		printf("Registration correctly completed...\n");
	}

	mysql_stmt_close(prepared_stmt);

}

static void register_customer(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[12];

	// Input for the registration routine
	char cf[17];
	char nome[46]; 
	char cognome[46]; 
	char matricola[7];
	char giorno[3];
	char mese[3];
	char anno[5];
	char mail[46]; 
	char telefono[11]; 
	char fax[12];
	char via[46];
	char civico[6];
	char citta[46];
	MYSQL_TIME nascita;
	memset(&nascita,0, sizeof(nascita));
	int numerot, numerof;

	// Get the required information
	printf("\nTax code: ");
	getInput(17, cf, false);
	printf("Name: ");
	getInput(46, nome, false);
	printf("Surname: ");
	getInput(46, cognome, false);
	printf("Officer ID: ");
	getInput(7, matricola, false);
	printf("Date of birth:\n");
	printf("Day: ");
	getInput(3, giorno, false);
	printf("Month: ");
	getInput(3, mese, false);
	printf("Year: ");
	getInput(5, anno, false);
	printf("Mail: ");
	getInput(46, mail, false);
	printf("Telephone: ");
	getInput(11, telefono, false);
	printf("Fax: ");
	getInput(12, fax, false);
	printf("Address:\n");
	printf("Street: ");
	getInput(46, via, false);
	printf("Street number: ");
	getInput(6, civico, false);
	printf("City: ");
	getInput(46, citta, false);

	nascita.day=atoi(giorno);
	nascita.month=atoi(mese);
	nascita.year=atoi(anno);
	nascita.day=atoi(giorno);
	nascita.month=atoi(mese);
	nascita.year=atoi(anno);
	numerot=atoi(telefono);
	numerof=atoi(fax);

	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call inserisci_cliente(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize register customer statement\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[0].buffer = cf;
	param[0].buffer_length = strlen(cf);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[1].buffer = nome;
	param[1].buffer_length = strlen(nome);

	param[2].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[2].buffer = cognome;
	param[2].buffer_length = strlen(cognome);

	param[3].buffer_type = MYSQL_TYPE_DATE; 		
	param[3].buffer = &nascita;
	param[3].buffer_length = sizeof(nascita);

	param[4].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[4].buffer = matricola;
	param[4].buffer_length = strlen(matricola);

	param[5].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[5].buffer = mail;
	param[5].buffer_length = strlen(mail);

	param[6].buffer_type = MYSQL_TYPE_LONG;
	param[6].buffer = &numerot;
	param[6].buffer_length = sizeof(numerot);

	param[7].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[7].buffer = via;
	param[7].buffer_length = strlen(via);

	param[8].buffer_type = MYSQL_TYPE_VAR_STRING; 		
	param[8].buffer = civico;
	param[8].buffer_length = strlen(civico);

	param[9].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[9].buffer = citta;
	param[9].buffer_length = strlen(citta);

	param[10].buffer_type = MYSQL_TYPE_LONG;
	param[10].buffer = &numerof;
	param[10].buffer_length = sizeof(numerof);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for register customer\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "An error occurred while registering the customer.");
	} else{
		printf("Registration correctly completed...\n");
	}

	mysql_stmt_close(prepared_stmt);
}

static void add_another_mail(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[2];
	
	// Input for the registration routine
	char cf[17];
	char mail[46];

	printf("\nTax code: ");
	getInput(17, cf, false);
	printf("Mail: ");
	getInput(46, mail, false);


	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call aggiungi_mail(?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize add mail to customer statement\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[0].buffer = cf;
	param[0].buffer_length = strlen(cf);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[1].buffer = mail;
	param[1].buffer_length = strlen(mail);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for add mail\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "An error occurred while adding mail.");
	}else{
		printf("Operation correctly completed...\n");
	}

	mysql_stmt_close(prepared_stmt);
}

static void add_another_telephone(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[2];
	
	// Input for the registration routine
	char cf[17];
	char telefono[11];
	int numero;

	printf("\nTax code: ");
	getInput(17, cf, false);
	printf("Telephone number: ");
	getInput(11, telefono, false);

	numero=atoi(telefono);


	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call aggiungi_telefono(?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize add telephone to customer statement\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[0].buffer = cf;
	param[0].buffer_length = strlen(cf);

	param[1].buffer_type = MYSQL_TYPE_LONG;
	param[1].buffer = &numero;
	param[1].buffer_length = sizeof(numero);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for add telephone\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "An error occurred while adding telephone.");
	}else{
		printf("Operation correctly completed...\n");
	}

	mysql_stmt_close(prepared_stmt);
}

static void add_another_fax(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[2];
	
	// Input for the registration routine
	char cf[17];
	char fax[12];
	int numero;

	printf("\nTax code: ");
	getInput(17, cf, false);
	printf("Fax: ");
	getInput(12, fax, false);
	numero=atoi(fax);

	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call aggiungi_fax(?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize add fax to customer statement\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[0].buffer = cf;
	param[0].buffer_length = strlen(cf);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[1].buffer = &numero;
	param[1].buffer_length = sizeof(numero);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for add fax\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "An error occurred while adding fax.");
	}else{
		printf("Operation correctly completed...\n");
	}

	mysql_stmt_close(prepared_stmt);
}

static void add_another_address(MYSQL *conn){
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[4];
	
	// Input for the registration routine
	char cf[17];
	char via[46];
	char civico[6];
	char citta[46];

	printf("\nTax code: ");
	getInput(17, cf, false);
	printf("Address:\n");
	printf("Street: ");
	getInput(46, via, false);
	printf("Street number: ");
	getInput(6, civico, false);
	printf("City: ");
	getInput(46, citta, false);


	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call aggiungi_indirizzo(?, ?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize add address to customer statement\n\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[0].buffer = cf;
	param[0].buffer_length = strlen(cf);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[1].buffer = via;
	param[1].buffer_length = strlen(via);

	param[2].buffer_type = MYSQL_TYPE_VAR_STRING; 		
	param[2].buffer = civico;
	param[2].buffer_length = strlen(civico);

	param[3].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[3].buffer = citta;
	param[3].buffer_length = strlen(citta);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for add address\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "An error occurred while adding address.");
	}else{
		printf("Operation correctly completed...\n");
	}

	mysql_stmt_close(prepared_stmt);
}

void run_as_commercial(MYSQL *conn)
{
	char options[7] = {'1','2','3','4','5','6','7'};
	char op;
	
	printf("Switching to commercial role...\n");

	if(!parse_config("users/commerciale.json", &conf)) {
		fprintf(stderr, "Unable to load commercial configuration\n");
		exit(EXIT_FAILURE);
	}

	if(mysql_change_user(conn, conf.db_username, conf.db_password, conf.database)) {
		fprintf(stderr, "mysql_change_user() failed\n");
		exit(EXIT_FAILURE);
	}

	while(true) {
		printf("\033[2J\033[H");
		printf("*** What should I do for you? ***\n\n");
		printf("1) Register customer\n");
		printf("2) Register company\n");
		printf("3) Add another mail to a customer\n");
		printf("4) Add another number telephone to a customer\n");
		printf("5) Add another fax to a customer\n");
		printf("6) Add another address to a customer\n");
		printf("7) Quit\n");

		op = multiChoice("Select an option", options, 7);

		switch(op) {
			case '1':
				register_customer(conn);
				break;

			case '2':
				register_company(conn);
				break;

			case '3':
				add_another_mail(conn);
				break;

			case '4':
				add_another_telephone(conn);
				break;

			case '5':
				add_another_fax(conn);
				break;				

			case '6':
				add_another_address(conn);
				break;

			case '7':
				return;
				
			default:
				fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
				abort();
		}

		getchar();
	}
}
