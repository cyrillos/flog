FROM fedora:24
RUN dnf install -y gcc make libffi-devel
COPY . /flog
WORKDIR /flog
RUN make clean && make -j $(nproc)
