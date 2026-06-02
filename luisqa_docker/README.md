# luisqa_docker — Banco de Dados MySQL com Docker

Ambiente de banco de dados MySQL containerizado com Docker, desenvolvido como projeto prático da disciplina de Banco de Dados — FATEC ADS.

---

## Modelo de Dados

O banco `fatec1sem2026` contém as seguintes tabelas:

| Tabela | Descrição |
|---|---|
| `departamento` | Setores da empresa |
| `funcionario` | Colaboradores vinculados a departamentos |
| `cliente` | Clientes cadastrados |
| `produto` | Catálogo de produtos |
| `pedido` | Pedidos realizados por clientes |
| `detalhepedido` | Itens de cada pedido |
| `fornecedor` | Fornecedores cadastrados |
| `equipe` | Equipes e seus líderes |
| `atividade` | Atividades atribuídas a funcionários |
| `reuniao` | Reuniões agendadas |

---

## Tecnologias

![MySQL](https://img.shields.io/badge/MySQL-8.0-4479A1?style=flat&logo=mysql&logoColor=white)
![Docker](https://img.shields.io/badge/Docker-2496ED?style=flat&logo=docker&logoColor=white)

---

## Como rodar

**Pré-requisitos:** Docker e Docker Compose instalados.

**1. Clone o repositório**
```bash
git clone https://github.com/seu-usuario/luisqa_docker.git
cd luisqa_docker
```

**2. Configure as variáveis de ambiente**
```bash
cp .env.example .env
```
Abra o `.env` e preencha com suas credenciais.

**3. Suba o container**
```bash
docker compose up -d
```

O script `init.sql` é executado automaticamente na primeira vez, criando todas as tabelas e inserindo os dados.

**4. Verifique se está rodando**
```bash
docker ps
```

---

## Conexão

| Campo | Valor |
|---|---|
| Host | `localhost` |
| Porta | `3307` |
| Banco | `fatec1sem2026` |
| Usuário | definido no `.env` |

Compatível com DBeaver, MySQL Workbench ou qualquer cliente MySQL.

---

## Parar o container

```bash
docker compose down
```

Para remover também os dados do volume:
```bash
docker compose down -v
```

---

## Autor

**Luis Kleber de Arruda**  
Estudante de ADS — FATEC
