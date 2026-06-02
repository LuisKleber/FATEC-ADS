-- Script MySQL corrigido para Docker
-- Banco: fatec1sem2026

DROP DATABASE IF EXISTS fatec1sem2026;
CREATE DATABASE fatec1sem2026;
USE fatec1sem2026;

-- =========================
-- TABELAS
-- =========================

CREATE TABLE departamento (
    departamentoID INT PRIMARY KEY,
    nome VARCHAR(100),
    localizacao VARCHAR(100)
);

CREATE TABLE funcionario (
    funcionarioID INT PRIMARY KEY,
    nome VARCHAR(100),
    email VARCHAR(255),
    departamento INT,
    datacontratacao DATE,
    salario DECIMAL(10,2),
    FOREIGN KEY (departamento)
        REFERENCES departamento(departamentoID)
);

CREATE TABLE cliente (
    clienteID INT PRIMARY KEY,
    nome VARCHAR(100),
    email VARCHAR(255),
    endereco VARCHAR(255),
    status BOOLEAN
);

CREATE TABLE produto (
    produtoID INT PRIMARY KEY,
    descricao VARCHAR(100),
    preco DECIMAL(12,2)
);

CREATE TABLE pedido (
    pedidoID INT PRIMARY KEY,
    datapedido DATE,
    cliente INT,
    funcionarioID INT,
    status VARCHAR(20),
    FOREIGN KEY (cliente)
        REFERENCES cliente(clienteID),
    FOREIGN KEY (funcionarioID)
        REFERENCES funcionario(funcionarioID)
);

CREATE TABLE detalhepedido (
    detalhepedidoID INT PRIMARY KEY,
    quantidade INT,
    pedido INT,
    produto INT,
    FOREIGN KEY (pedido)
        REFERENCES pedido(pedidoID),
    FOREIGN KEY (produto)
        REFERENCES produto(produtoID),
    CONSTRAINT CHK_Quantidade CHECK (quantidade > 0)
);

CREATE TABLE fornecedor (
    fornecedorID INT PRIMARY KEY,
    nome VARCHAR(100),
    contato VARCHAR(100),
    telefone VARCHAR(20),
    email VARCHAR(255)
);

CREATE TABLE equipe (
    equipeID INT PRIMARY KEY,
    nome VARCHAR(100),
    liderID INT,
    descricao VARCHAR(255),
    FOREIGN KEY (liderID)
        REFERENCES funcionario(funcionarioID)
);

CREATE TABLE atividade (
    atividadeID INT PRIMARY KEY,
    descricao VARCHAR(255),
    data_atividade DATE,
    funcID INT,
    FOREIGN KEY (funcID)
        REFERENCES funcionario(funcionarioID)
);

CREATE TABLE reuniao (
    reuniaoID INT PRIMARY KEY,
    assunto VARCHAR(100),
    local_reuniao VARCHAR(100),
    data_reuniao DATE,
    hora TIME
);

-- =========================
-- INSERTS
-- =========================

INSERT INTO departamento (departamentoID, nome, localizacao)
VALUES
(1,'TI','Térreo'),
(2,'Financeiro','1º Andar'),
(3,'Pessoal','2º Andar'),
(4,'Marketing','2º Andar'),
(5,'RH','1º Andar'),
(6,'Logística','Galpão');

INSERT INTO funcionario
(funcionarioID, nome, email, departamento, datacontratacao, salario)
VALUES
(1,'Carlos Souza Junior','carlos@empresa.com',1,'2025-03-01',4200.00),
(2,'João Silva','joao@empresa.com',1,'2025-06-20',4000.00),
(3,'Ana Costa','ana@empresa.com',2,'2025-05-10',3800.00),
(4,'Bruno Alves','bruno@empresa.com',3,'2025-05-11',4100.00),
(5,'Fernanda Souza','fernanda@empresa.com',4,'2025-05-12',4500.00),
(6,'Ricardo Lima','ricardo@empresa.com',5,'2025-05-13',3900.00);

INSERT INTO cliente
(clienteID, nome, email, endereco, status)
VALUES
(1,'Maria Lima','maria.lima@novoemail.com','Rua Nova, 789',1),
(2,'Pedro Lima','pedro@email.com.br','Rua A, 123',1),
(3,'Lucas Pereira','lucas@email.com','Rua B, 456',1),
(4,'Mariana Torres','mariana@email.com','Rua C, 789',1),
(5,'Felipe Gomes','felipe@email.com','Rua D, 321',1);

INSERT INTO produto
(produtoID, descricao, preco)
VALUES
(1,'Notebook',3600.00),
(2,'Mouse',60.00),
(3,'Teclado',75.00),
(4,'Monitor',1200.00),
(5,'Impressora',800.00),
(6,'Cadeira Gamer',950.00),
(7,'HD Externo',250.00);

INSERT INTO pedido
(pedidoID, cliente, funcionarioID, datapedido, status)
VALUES
(1,1,1,'2025-04-01','Finalizado'),
(2,1,1,'2025-05-01','Finalizado'),
(3,2,2,'2025-04-01','Pendente'),
(5,3,3,CURDATE(),'Em processamento'),
(6,4,4,CURDATE(),'Em processamento');

INSERT INTO detalhepedido
(detalhepedidoID, pedido, produto, quantidade)
VALUES
(1,1,1,1),
(2,1,3,1),
(3,1,2,1),
(4,2,2,7),
(5,3,3,4),
(6,5,4,1),
(7,5,7,2),
(8,6,5,1),
(9,6,6,1);

INSERT INTO fornecedor
(fornecedorID, nome, contato, telefone, email)
VALUES
(1,'TechSuprimentos','João','(19)99999-9999','joao@tech.com.br'),
(2,'OfficeSupplies','Carla','(11)97777-7777','carla@office.com');

INSERT INTO equipe
(equipeID, nome, liderID, descricao)
VALUES
(1,'Equipe TI',1,'Equipe responsável pelos sistemas'),
(2,'Equipe RH',6,'Equipe responsável por pessoas');

INSERT INTO atividade
(atividadeID, descricao, data_atividade, funcID)
VALUES
(1,'Desenvolvimento do sistema','2025-05-10',1),
(2,'Atualização de banco de dados','2025-05-11',2);

INSERT INTO reuniao
(reuniaoID, assunto, local_reuniao, data_reuniao, hora)
VALUES
(1,'Planejamento','Sala 1','2025-05-20','09:00:00'),
(2,'Sprint Review','Sala 2','2025-05-21','14:00:00');

-- =========================
-- CONSULTAS ÚTEIS
-- =========================

SELECT * FROM departamento;
SELECT * FROM funcionario;
SELECT * FROM cliente;
SELECT * FROM produto;
SELECT * FROM pedido;
SELECT * FROM detalhepedido;
SELECT * FROM fornecedor;
