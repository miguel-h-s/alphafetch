# 🐺 alphafetch

Um buscador de informações do sistema (fetch) rápido, leve e modular, feito em C++20 para sistemas Linux.

## PRIMEIRAMENTE!
este projeto esta nas suas primeiras versões, quer customizar seu alphafetch? CODIGO FONTE! mudar algo? CODIGO FONTE! adicionar suporte ao KDE? CONTRIBUIÇÃO!
(não tem suporte ao KDE na parte de ricing, como o cursor, tema e icone)

![Screenshot](screenshots/fetch.png)

## 🚀 Funcionalidades

* **Rápido e Leve:** Feito em C++, sem interprets pesados.
* **Modular:** Cada informação (CPU, GPU, RAM) tem seu próprio arquivo `.cpp`.
* **Completo:** Mostra informações de Hardware, Sistema, Temas GTK e uso de Disco/RAM.
* **Design Limpo:** Alinhamento automático lado a lado com arte ASCII.

## 🛠️ Como Compilar e Instalar

### Pré-requisitos
Você precisará de um compilador que suporte C++20 (como o `g++` 10+) e do `make`. No Debian/Ubuntu, você resolve isso com:
```bash
sudo apt install build-essential
```

### instalação
1. clone o repositório(meio obvio)
2. entre na pasta do projeto(``cd alphaprojetcs-cpp`` por padrão)
3. compile!(`make`)
4. instale no sistema(opcional mais recomendado)
`sudo make install`

pronto! execute seu `alphafetch` de qualquer lugar no terminal!
