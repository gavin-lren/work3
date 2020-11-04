FROM gcc:10
WORKDIR /app/
COPY ./* ./
RUN gcc Operator_analysis.c -o Operator_analysis
RUN chmod +x Operator_analysis
