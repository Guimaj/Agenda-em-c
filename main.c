/*=====================================================
  Nome: André Guimarães Jorge RA: 22.118.115-9
  Nome: João Victor da Silva Couto RA: 22.118.022-7
=======================================================*/
#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include<string.h>
#include<locale.h>

typedef struct paciente{
  char nome[50],tel[20],email[30],RG[16],CPF[20],tipo_s[5],operadora[15],religiao[10],cidade[20],estado[3];
}Paciente;

typedef struct agenda{
  Paciente *p;
  int max;
  int user_cad;
}Agenda;
 
Agenda cria_agenda(int n){
  Agenda a;
  a.p = malloc(sizeof(Paciente)*n);
  a.max = n;
  a.user_cad = 0;
  return a;
}

void ler_bin(Agenda *a){
  FILE *arq;
  int cad;
  arq = fopen("Agenda_bin.txt","rb");
  if(arq == NULL){
    printf("Erro na abertura do arquivo!\n");
    exit(1);
  }
  fread(&cad,sizeof(cad),1,arq);
  fread(a->p,sizeof(Paciente),cad,arq);
  a->user_cad = cad;
}

void cadastraPessoa(Agenda *a){
  int i,opc;
  
  if(a->user_cad >= a->max){
    printf("Limite de pacientes atingidos!\n\n");
    setbuf(stdin, NULL);
    sleep(1);
    return;
  }
    printf("Nome: ");
    fgets(a->p[a->user_cad].nome,sizeof(a->p[a->user_cad].nome), stdin);
    printf("Telefone: ");
    fgets(a->p[a->user_cad].tel,sizeof(a->p[a->user_cad].tel), stdin);
    printf("Email: ");
    fgets(a->p[a->user_cad].email,sizeof(a->p[a->user_cad].email), stdin);
    printf("RG: ");
    fgets(a->p[a->user_cad].RG,sizeof(a->p[a->user_cad].RG), stdin);
    printf("CPF: ");
    fgets(a->p[a->user_cad].CPF,sizeof(a->p[a->user_cad].CPF), stdin);
    printf("Tipo Sanguineo: ");
    fgets(a->p[a->user_cad].tipo_s,sizeof(a->p[a->user_cad].tipo_s), stdin);
    printf("Operadora: ");
    fgets(a->p[a->user_cad].operadora,sizeof(a->p[a->user_cad].operadora), stdin);
    printf("Religião: ");
    fgets(a->p[a->user_cad].religiao,sizeof(a->p[a->user_cad].religiao), stdin);
    printf("Cidade: ");
    fgets(a->p[a->user_cad].cidade,sizeof(a->p[a->user_cad].cidade), stdin);
    printf("Estado: ");
    fgets(a->p[a->user_cad].estado,sizeof(a->p[a->user_cad].estado), stdin);
    a->user_cad++;
    setbuf(stdin,NULL);
    printf("Paciente Cadastrado!\n\n");
    sleep(1); 
}

void imprimePaciente(Paciente *p){
  printf("Nome: %s",p->nome);
  printf("Telefone: %s",p->tel);
  printf("Email: %s",p->email);
  printf("RG: %s",p->RG);
  printf("CPF: %s",p->CPF);
  printf("Tipo Sanguineo: %s",p->tipo_s);
  printf("Operadora: %s",p->operadora);
  printf("Religiao: %s",p->religiao);
  printf("Cidade: %s",p->cidade);
  printf("Estado: %s",p->estado);
  printf("\n");
}

int buscaRG(Agenda *a, char rg[]){
  int i;
  for(i=0;i<a->user_cad;i++){
      if(strcmp(rg, a->p[i].RG) == 0){
        return i;
      }
    }
  return -1;
}

int busca_e_imprime(Agenda *a){
  int i,busca = 0;
  char nome[50];
  printf("Digite o nome do paciente que deseja buscar:");
  fgets(nome,sizeof(nome),stdin);
  setbuf(stdin, NULL);

  for(i=0;i<a->user_cad;i++){
    if(strcmp(nome, a->p[i].nome) == 0){
      busca = 1;
      printf("====== Paciente ========\n\n");
      imprimePaciente(&a->p[i]);
      printf("\n");
    }
  }
  if(busca == 0){
    printf("Paciente não encontrado!\n\n");
    return -1; 
  }  
}

void deleta_paciente(Agenda *a){
  int id,i;
  char rg[16];
  printf("Digite o RG do paciente que deseja excluir: ");
  fgets(rg,sizeof(rg), stdin);
  id = buscaRG(a,rg);
  
  if(id == -1){
    printf("Paciente não encontrado!\n");
  }
  else{
    printf("======= Paciente =========\n\n");
    imprimePaciente(&a->p[id]);
    for(i=id;i<a->user_cad - 1;i++){
      a->p[i] = a->p[i+1];
    }
    puts("");
    printf("Paciente %s excluido com sucesso!\n",a->p[id].nome);
    a->user_cad--;
  }
}

void menualtera(Agenda *a){
  int opc, busca, id;
  char rg[16];
  busca = busca_e_imprime(a);
  
  if(a->user_cad == 0){
    printf("Não existem usuários cadastrados!\n\n");
  }
  if(busca != -1){
    printf("===== opções de alteração =======\n\n");
    printf("1 - Alterar nome\n2 - Alterar telefone\n3 - Alterar email\n4 - Alterar RG\n5 - Alterar CPF\n6 - Alterar tipo Sanguineo\n7 - Alterar operadora\n8 - Alterar religião\n9 - Alterar cidade\n10 - Alterar estado\n\n");
    
    printf("Digite uma opção: ");
    scanf("%d",&opc);
    setbuf(stdin,NULL);
    printf("Digite o RG do paciente que deseja alterar: ");
    fgets(rg,sizeof(rg), stdin);
    setbuf(stdin,NULL);
    id = buscaRG(a,rg);

    if(id == -1){
      printf("Paciente não encontrado!\n");
      sleep(1);
      return;
    }

    else if(id != -1){
      if(opc == 1){
        char nome[50];
        printf("Digite o novo nome: ");
        fgets(nome,sizeof(nome),stdin);
        setbuf(stdin, NULL);
        strcpy(a->p[id].nome,nome);
        puts("");
        printf("Nome alterado com sucesso!\n");
      }
      else if(opc == 2){
        char tel[20];
        printf("Digite o novo telefone: ");
        fgets(tel,sizeof(tel),stdin);
        setbuf(stdin, NULL);
        strcpy(a->p[id].tel,tel);
        puts("");
        printf("Telefone alterado com sucesso!\n");
      }
      else if(opc == 3){
        char email[30];
        printf("Digite o novo e-mail: ");
        fgets(email,sizeof(email),stdin);
        setbuf(stdin, NULL);
        strcpy(a->p[id].email,email);
        puts("");
        printf("E-mail alterado com sucesso!\n");
      }
      else if(opc == 4){
        char rg[16];
        printf("Digite o novo RG: ");
        fgets(rg,sizeof(rg),stdin);
        setbuf(stdin, NULL);
        strcpy(a->p[id].RG,rg);
        puts("");
        printf("RG alterado com sucesso!\n");
      }
      else if(opc == 5){
        char cpf[20];
        printf("Digite o novo CPF: ");
        fgets(cpf,sizeof(cpf),stdin);
        setbuf(stdin, NULL);
        strcpy(a->p[id].CPF,cpf);
        puts("");
        printf("CPF alterado com sucesso!\n");
      }
      else if(opc == 6){
        char tipo[4];
        printf("Digite o novo tipo sanguineo: ");
        fgets(tipo,sizeof(tipo),stdin);
        setbuf(stdin, NULL);
        strcpy(a->p[id].tipo_s,tipo);
        puts("");
        printf("Tipo sanguineo alterado com sucesso!\n");
      }
      else if(opc == 7){
        char operadora[15];
        printf("Digite a nova operadora: ");
        fgets(operadora,sizeof(operadora),stdin);
        setbuf(stdin, NULL);
        strcpy(a->p[id].operadora,operadora);
        puts("");
        printf("Operadora alterada com sucesso!\n");
      }
      else if(opc == 8){
        char religiao[10];
        printf("Digite a nova religião: ");
        fgets(religiao,sizeof(religiao),stdin);
        setbuf(stdin, NULL);
        strcpy(a->p[id].religiao,religiao);
        puts("");
        printf("Religião alterada com sucesso!\n");
      }
      else if(opc == 9){
        char cidade[20];
        printf("Digite a nova cidade: ");
        fgets(cidade,sizeof(cidade),stdin);
        setbuf(stdin, NULL);
        strcpy(a->p[id].cidade,cidade);
        puts("");
        printf("Cidade alterada com sucesso!\n");
      }
      else if(opc == 10){
        char estado[3];
        printf("Digite o novo estado: ");
        fgets(estado,sizeof(estado),stdin);
        strcpy(a->p[id].estado,estado);
        puts("");
        printf("estado alterado com sucesso!\n");
        setbuf(stdin,NULL);
      }
    }
  }
}

void imprimeAgenda(Agenda *a){
  int i;
  if(a->user_cad > 0){
    for(i=0;i<a->user_cad;i++){
      imprimePaciente(&a->p[i]);
      puts("");
    }
  }
  else{
    printf("Não há pacientes cadastrados!\n\n");
  }
}

void salvar_bin(Agenda *a){
  Paciente p;
  FILE *arq;
  arq = fopen("Agenda_bin.txt","wb");
  fwrite(&a->user_cad,sizeof(int),1,arq);
  fwrite(a->p,sizeof(Paciente),a->user_cad,arq);
  printf("Agenda salva em modo bin com sucesso!\n");
  fclose(arq);
}

void gravar_txt(Agenda *a){
  FILE *arq;
  int i;
  arq = fopen("Agenda.txt","w");
  fprintf(arq,"%d\n",a->user_cad);
  for(i=0;i<a->user_cad;i++){
    fprintf(arq,"%s",a->p[i].nome);
    fprintf(arq,"%s",a->p[i].tel);
    fprintf(arq,"%s",a->p[i].email);
    fprintf(arq,"%s",a->p[i].RG);
    fprintf(arq,"%s",a->p[i].CPF);
    fprintf(arq,"%s",a->p[i].tipo_s);
    fprintf(arq,"%s",a->p[i].operadora);
    fprintf(arq,"%s",a->p[i].religiao);
    fprintf(arq,"%s",a->p[i].cidade);
    fprintf(arq,"%s",a->p[i].estado);
  }
  printf("Agenda salva em modo texto com sucesso!\n");
  fclose(arq);
}
void ler_txt(Agenda *a){
  FILE *arq;
  int cad,i;
  arq = fopen("Agenda.txt","r");
  if(arq == NULL){
    printf("Erro na abertura do arquivo!\n");
    exit(1);
  }
  fscanf(arq,"%d\n",&cad);
  setbuf(stdin,NULL);
  for(i=0;i<cad;i++){
    fgets(a->p[i].nome,sizeof(a->p[i].nome),arq);
    fgets(a->p[i].tel,sizeof(a->p[i].tel),arq);
    fgets(a->p[i].email,sizeof(a->p[i].email),arq);
    fgets(a->p[i].RG,sizeof(a->p[i].RG),arq);
    fgets(a->p[i].CPF,sizeof(a->p[i].CPF),arq);
    fgets(a->p[i].tipo_s,sizeof(a->p[i].tipo_s),arq);
    fgets(a->p[i].operadora,sizeof(a->p[i].operadora),arq);
    fgets(a->p[i].religiao,sizeof(a->p[i].religiao),arq);
    fgets(a->p[i].cidade,sizeof(a->p[i].cidade),arq);
    fgets(a->p[i].estado,sizeof(a->p[i].estado),arq);
  }
  printf("Agenda em modo texto lida com sucesso!\n");
  a->user_cad = cad;
  fclose(arq);
}

void menu_txt(Agenda *a){
  int opc;
  printf("1 - Gravar agenda em modo texto\n");
  printf("2 - Ler agenda em modo texto\n");
  printf("3 - Voltar ao menu principal\n");
  printf("Digite uma opção: ");
  scanf("%d",&opc);
  setbuf(stdin, NULL);

  if(opc == 1){
    gravar_txt(a);
  }
  else if(opc == 2){
    ler_txt(a);
  }
  else if(opc == 3){
    return;
  }
}

void destroiAgenda(Agenda *a){
  free(a->p);
}

void menuPrincipal(Agenda a){
  setbuf(stdin,NULL);
  int menu = 0;
  printf("==============================\n");
  printf("      Agenda de Pacientes\n");
  printf("==============================\n\n");
  printf("Digite a opção desejada por favor:\n\n1 - Cadastrar paciente.\n2 - Listar todos pacientes.\n3 - Remover paciente.\n4 - Alterar paciente.\n5 - Buscar paciente.\n6 - Opções Avançadas.\n7 - Sair.\n\n");
  printf("Digite uma opção: ");
  scanf("%d", &menu);
  setbuf(stdin,NULL);

  switch(menu){
    case 1:
      printf("======== Cadastro de Pacientes =======\n\n");
      cadastraPessoa(&a);
      menuPrincipal(a);
    break;
    case 2:
      printf("======== Lista de Pacientes ========\n\n");
      imprimeAgenda(&a);
      sleep(1);
      menuPrincipal(a);
    break;
    case 3:
      deleta_paciente(&a);
      sleep(1);
      menuPrincipal(a);
    break;
    case 4:
      printf("====== Menu de Alteração =======\n\n");
      menualtera(&a);
      sleep(1);
      menuPrincipal(a);
    break;
    case 5:
      printf("===== Busca de Pacientes ======\n\n");
      busca_e_imprime(&a);
      sleep(1);
      menuPrincipal(a);
    break;
    case 6:
      menu_txt(&a);
      sleep(1);
      menuPrincipal(a);
    break;
    case 7:
      salvar_bin(&a);
    break;
    default:
      printf("\nPor favor digite uma opção válida!\n\n");
      sleep(2);
      menuPrincipal(a);
    break;
  }
}

int main(){
  setlocale(LC_ALL, "Portuguese");
  Agenda a;
  a = cria_agenda(100);
  ler_bin(&a);
  menuPrincipal(a);
  destroiAgenda(&a);
  system("pause");
 return 0;
}

