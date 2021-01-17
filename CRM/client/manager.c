#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"


static void create_proposal(MYSQL *conn) {
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[2];

	// Input for the registration routine
	char codice[11];
	char descrizione[46];

	printf("\nProposal ID: ");
	getInput(10, codice, false);
	printf("Description: ");
	getInput(45, descrizione, false);


	if(!setup_prepared_stmt(&prepared_stmt, "call inserisci_proposta(?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize create proposal statement\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));
	
	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[0].buffer = codice;
	param[0].buffer_length = strlen(codice);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[1].buffer = descrizione;
	param[1].buffer_length = strlen(descrizione);	

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for create proposal\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "An error occured while creating new proposal\n");
	}else{
		printf("Proposal created successfully...\n");
	}

	mysql_stmt_close(prepared_stmt);

}

static void terminate_proposal(MYSQL *conn) {
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[2];

	// Input for the registration routine
	char codice[11];


	if(!setup_prepared_stmt(&prepared_stmt, "call proposte_attive()", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize active proposals list statement\n", false);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "Could not retrieve active proposals list\n");
	}

	// Dump the result set
	dump_result_set(conn, prepared_stmt, "\nList of active proposals");
	mysql_stmt_next_result(prepared_stmt);
	mysql_stmt_close(prepared_stmt);

	printf("\nProposal ID: ");
	getInput(10, codice, false);

	if(!setup_prepared_stmt(&prepared_stmt, "call termina_proposta(?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize marks proposal finished statement\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));
	
	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[0].buffer = codice;
	param[0].buffer_length = strlen(codice);
	
	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for marks proposal finished\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error(prepared_stmt, "An error occured while marking proposal finished\n");
	}else{
		printf("Request completed successfully...\n");
	}

	mysql_stmt_close(prepared_stmt);

}

static void add_officer(MYSQL *conn)
{
	MYSQL_STMT *prepared_stmt;
	MYSQL_BIND param[5];

	// Input for the registration routine
	char matricola[46];
	char nome[46];
	char cognome[46];
	char password[46];

	// Get the required information
	printf("\nUser ID: ");
	getInput(46, matricola, false);
	printf("Name: ");
	getInput(46, nome, false);
	printf("Surname: ");
	getInput(46, cognome, false);
	printf("Password: ");
	getInput(46, password, true);
		
	// Prepare stored procedure call
	if(!setup_prepared_stmt(&prepared_stmt, "call aggiungi_funzionario(?, ?, ?, ?)", conn)) {
		finish_with_stmt_error(conn, prepared_stmt, "Unable to initialize user insertion statement\n", false);
	}

	// Prepare parameters
	memset(param, 0, sizeof(param));

	param[0].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[0].buffer = matricola;
	param[0].buffer_length = strlen(matricola);

	param[1].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[1].buffer = nome;
	param[1].buffer_length = strlen(nome);

	param[2].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[2].buffer = cognome;
	param[2].buffer_length = strlen(cognome);	

	param[3].buffer_type = MYSQL_TYPE_VAR_STRING;
	param[3].buffer = password;
	param[3].buffer_length = strlen(password);

	if (mysql_stmt_bind_param(prepared_stmt, param) != 0) {
		finish_with_stmt_error(conn, prepared_stmt, "Could not bind parameters for user insertion\n", true);
	}

	// Run procedure
	if (mysql_stmt_execute(prepared_stmt) != 0) {
		print_stmt_error (prepared_stmt, "An error occurred while adding the user.");
	} else {
		printf("User correctly added...\n");
	}

	mysql_stmt_close(prepared_stmt);
}


void run_as_manager(MYSQL *conn)
{
	char options[4] = {'1','2', '3', '4'};
	char op;
	
	printf("Switching to manager role...\n");

	if(!parse_config("users/manager.json", &conf)) {
		fprintf(stderr, "Unable to load manager configuration\n");
		exit(EXIT_FAILURE);
	}

	if(mysql_change_user(conn, conf.db_username, conf.db_password, conf.database)) {
		fprintf(stderr, "mysql_change_user() failed\n");
		exit(EXIT_FAILURE);
	}

	while(true) {
		printf("\033[2J\033[H");
		printf("*** What should I do for you? ***\n\n");
		printf("1) Create new proposal\n");
		printf("2) Terminate proposal\n");
		printf("3) Add new officer\n");
		printf("4) Quit\n");

		op = multiChoice("Select an option", options, 4);

		switch(op) {
			case '1':
				create_proposal(conn);
				break;
			
			case '2':
				terminate_proposal(conn);
				break;

			case '3':
				add_officer(conn);
				break;

			case '4':
				return;
				
			default:
				fprintf(stderr, "Invalid condition at %s:%d\n", __FILE__, __LINE__);
				abort();
		}

		getchar();
	}
}
