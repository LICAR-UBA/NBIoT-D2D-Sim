%https://www.lawebdelprogramador.com/foros/Matlab/1635976-Canal-de-Rayleigh.html
%https://en.wikipedia.org/wiki/Rayleigh_fading

% Obtencion de N amplitudes de un canal con fading por efecto multitrayectoria

% Inicializacion de parametros

N=1000; % Numero de amplitudes a obtener de las señales resultantes del efecto multitrayectoria

Xo=1;   % Amplitud de las sinusoides

fo=1;   % Frecuencia de las sinusoides

Np=4;   % Numero de periodos de las sinusiodes

Ncomp=100; % Numero de señales superpuestas

Nhist=50;  % Numero de intervalos para histograma

 

% Parametros de la simulacion

Fs=20*fo;       % Muestreo sinusiodes a frecuencia 20*fo

Ts=1/Fs;        % Periodo de muestreo

Tfin=Np/fo;     % Instante final

t=0:1/Fs:Tfin;  % Instantes de muestreo

Nfin=length(t); % Num. instantes muestreo

To=1/fo;        % Periodo sinusoides

No=round(To*(Nfin-1)/Tfin); % Num. muestras en un periodo

 

% Bucle principal de simulacion

for n=1:N

  x=zeros(1,Nfin);

  for nf=1:Ncomp

    fase=2*pi*rand(1)-pi;

    amp=2*rand(1)-1;

    xtmp=amp*cos(2*pi*fo*t+fase);

    x=x+xtmp;

  end

  R(n)=max(x); % Medicion de amplitud resultante

end

hist(R,Nhist)

pause()
