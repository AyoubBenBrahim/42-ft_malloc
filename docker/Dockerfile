FROM debian:buster

# Update the package repository and install necessary libraries and tools
RUN apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y build-essential \
                       clang \
                       wget \
                       make \
                       cmake \
                       libc6-dev-i386\
                       libssl-dev \
                       libreadline-dev \
                       libncurses-dev \
                       libffi-dev \
                       libxml2-dev \
                       libxslt-dev \
                       zlib1g-dev \
                       git \
                       curl \
                       tar \
                       vim \
                       file \
                       binutils \
                       bsdmainutils
                    #    gdb \
                    #    python3 \
                    #     python3-dev \
                    #     python3-pip

WORKDIR /ft_malloc

COPY . /ft_malloc

# Install Zsh
RUN apt-get update && apt-get install -y zsh

# Set Zsh as the default shell
RUN chsh -s $(which zsh)


# Install Oh My Zsh
RUN sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

# Download and extract Pwndbg portable version

RUN wget https://github.com/pwndbg/pwndbg/releases/download/2023.07.17-pkgs/pwndbg_2023.07.17_amd64.deb \
    && dpkg -i pwndbg_2023.07.17_amd64.deb

RUN /bin/zsh -c "source ~/.zshrc"

CMD ["tail", "-f", "/dev/null"]

