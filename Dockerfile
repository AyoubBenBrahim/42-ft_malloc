FROM node:latest AS build
WORKDIR /app
COPY package*.json ./
RUN npm install
COPY . .
RUN npm run build

FROM nginx:latest
COPY --from=build /app/dist /usr/share/nginx/html
CMD ["nginx", "-g", "daemon off"]

in Ansible context generate a playbook that do the follwing tasks on localhost as hosts, try to do each task independently then join them in one playbook

1- remove the existing userGroup "group-to-remove"
2- removes the exists user "user-to-remove"
3- modify the existing user "user-to-modify" setting the shell to /bin/bash
4- generates ssh keypaires for the user "user-to-modify"

