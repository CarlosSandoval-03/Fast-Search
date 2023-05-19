FROM gcc:13.1.0

WORKDIR /home/fast_search
COPY . .
RUN make build
RUN ./build/run_pre_process

EXPOSE 8080

CMD ["./build/server"]
