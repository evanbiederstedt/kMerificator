FROM ubuntu:20.04

LABEL authors="Evan Biederstedt (evan.biederstedt@gmail.com)" \
      version.image="0.1.0" \
      source.kmerificator="https://github.com/evanbiederstedt/kMerificator" \
      source.original_kmerificator="https://github.com/AlexanderDilthey/kMerificator"      

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y g++ build-essential libboost-all-dev git 


RUN git clone https://github.com/evanbiederstedt/kMerificator.git && \
    cd kMerificator && \
    git checkout develop && \
    make all

## executable in kMerificator/bin, './kMerificator'

