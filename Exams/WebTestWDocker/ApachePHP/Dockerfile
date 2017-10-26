FROM tutum/apache-php
RUN bash
RUN apt-get update
RUN apt-get install git -y
RUN rm *
WORKDIR /root
RUN git clone https://github.com/opencart/opencart
RUN mv opencart/upload/config-dist.php opencart/upload/config.php
RUN mv opencart/upload/admin/config-dist.php opencart/upload/admin/config.php
RUN mv opencart/upload/* /app
RUN chmod -R 777 /app
