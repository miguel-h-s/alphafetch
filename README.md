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

## 📋 requisitos pra funções especiais
- **Para a Música:** playerctl (responsável por detectar o que está tocando no Spotify, navegadores, etc.).
```bash
sudo apt install playerctl
```

- **para as Barras de Progresso (RAM/Disco):** O programa usa fontes Unicode padrão. Para melhor visualização dos ícones (se você decidir colocá-los futuramente), recomendamos o uso de uma **Nerd Font** no seu terminal (como a JetBrainsMono Nerd Font).

- **LEMBRANDO:** o AlphaFetch foi desenvolvido e testado no **Debian 13(Trixie) até o momento, mas servidores do discord estão testando em outras distros(como o Gentoo)!

## 🛠️ Como Compilar e Instalar

### Pré-requisitos
Você precisará de um compilador que suporte C++20 (como o `g++` 10+) e do `make`. No Debian/Ubuntu, você resolve isso com:
```bash
sudo apt install build-essential
```

### instalação
1. clone o repositório
2. entre na pasta do projeto(``cd alphafetch`` por padrão)
3. compile!(`make`)
4. instale no sistema(opcional, mas recomendado)
`sudo make install`

pronto! execute seu `alphafetch` de qualquer lugar no terminal!
