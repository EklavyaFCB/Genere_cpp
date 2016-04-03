clear all

filename = 'F_signal.m'; % Ce fichier contient les valeurs des points des signaux
nomfichier = 'Options.m'; % Ce fichier contient le choix l'affichage des signaux

A=importdata(filename); % On prend toutes les valeurs du fichier F_signal.m
F=textread(nomfichier,'%c');

G=F.';
H=G(1:3); % H contient les options d'affichage de la courbe pour le signal filtre
J=G(4:6); % J contient les options d'affichage de la courbe pour le signal non-filtre
M=size(A);
S=M(:,1); % On determine le nombre de lignes de la matrice A, soit le nombre de points
V=(0:1:S-1); % Creation d'une matrice allant de 0 au nombre de points du signal
x=A(:,1); % x contient les valeurs du signal filtre
y=A(:,2); % y contient les valeurs du signal non-filtre

plot(V',x,H,V',y,J); % On met tout les valeurs sur un graph 
xlabel('time'); % Le titre de l'axe-x vaut "time"
ylabel('amplitude'); % Le titre de l'axe-y vaut "amplitude"
title('Signal'); % Le titre du graph est "signal"

pause(10); % Le graph est affich? pendant 10 secondes
