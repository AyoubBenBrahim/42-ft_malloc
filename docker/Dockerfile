
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
                       vim \
                       file \
                       binutils \
                       bsdmainutils\
                       gdb

WORKDIR /ft_malloc

COPY . /ft_malloc

# Install Zsh
RUN apt-get update && apt-get install -y zsh

# Set Zsh as the default shell
RUN chsh -s $(which zsh)

# Switch to Zsh

# Install Oh My Zsh
RUN sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

SHELL ["/bin/zsh", "-c"]

CMD ["tail", "-f", "/dev/null"]