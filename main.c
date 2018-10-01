#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include <mysqld_error.h>
#include <locale.h>


int main(int argc, char *argv[]) {
	
	setlocale(LC_ALL,"Portuguese");

	
	MYSQL *link;
	
	link = mysql_init(NULL);//inicializa  ponteiro que armz conexao com bd
	
	
	//verifica se houve erro na inicializacao
	if(link == NULL)
	{
	  printf("%s \n",mysql_error(link));
	}
	
	//faz conexao com bd e verifica se funciou
	//parametros  (ip, usuario, senha, banco, nº porta, socket unix, e flag cliente)
	if(mysql_real_connect(link,"localhost","root","","biblioteca",3306,NULL,0) == NULL)
	{
		printf("%s \n",mysql_error(link));
		mysql_close(link);
	}
	
	//executa a consulta no banco de dados	
	mysql_query(link,"select * from usuario");
	
	//armazena resultado em ponteiro de struct		
	MYSQL_RES * res = mysql_store_result(link);
	
	//verifica a existência de resultados	
	if(res == NULL)
	{
	 printf("Nenhum resultado\n");	
	 mysql_close(link);
	}
	
	//armz o nº de campos obtidos da tabela bd	
	int num_campos = mysql_num_fields(res);
	//printf("%i\n",num_campos);
		
		
	//usada para amz nome das colunas
	MYSQL_FIELD *campoNome;
	//usada para armz os registros em linhas para iterar
	MYSQL_ROW linha;
	
	printf("Resultado(s), tabela de usuários:\n\n");
	
	//iteracao e exibicao de resultados por coluna
	while(linha = mysql_fetch_row(res))
	{
		int x;
		for (x=0;x<num_campos;x++)	
		{
			if(x==0)
			{
				while(campoNome = mysql_fetch_field(res))
				{
					printf("%s ", campoNome->name);
				}
				printf("\n");
			}
			
			printf("%s ",linha[x]?linha[x]:"NULL");
		}
	}
	printf("\n********************************");
	//libera a memória
	mysql_free_result(res);
	//fecha a conexão
	mysql_close(link);
	
	return 0;
}
