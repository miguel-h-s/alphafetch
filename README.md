# 🐺 alphafetch

Um buscador de informações do sistema (fetch) rápido, leve e modular, feito em C++20 para sistemas Linux.

> ⚠️ **Aviso:** Este projeto está nas suas primeiras versões! Quer customizar seu alphafetch? **CÓDIGO FONTE!** Mudar algo? **CÓDIGO FONTE!** Adicionar suporte ao KDE? **CONTRIBUIÇÃO!**
> *(Atualmente não há suporte ao KDE na parte de ricing, como detecção de cursor, tema e ícone).*

## 📸 demonstração
![print de alpha](./screenshots/screenshot_gatito.png)
![print do grande Tux](./screenshots/screenshot_tux.png)

## 🚀 Funcionalidades

* **Rápido e Leve:** Feito em C++, sem interpretadores pesados.
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
2. entre na pasta do projeto(``cd alphafetch-cpp`` por padrão)
3. compile!(`make`)
4. instale no sistema(opcional mais recomendado)
`sudo make install`

pronto! execute seu `alphafetch` de qualquer lugar no terminal!
