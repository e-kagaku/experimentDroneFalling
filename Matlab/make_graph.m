function make_graph()
  fileName = fullfile('data','ts3.TXT');
  file1 = fopen(fileName);

  index_num = 10;
  data_index = textscan(file1,'%s',index_num,'Delimiter',',')
  data_value = textscan(file1,'%{ddMMyy}D %{HHmmssSS}D %f %f %f %f %f %f %f','Delimiter',',')
%   
  data_matrix = cell2mat(data_value(:,3:9));

  matrix_index = 1:size(data_matrix,1);
  latitude = data_matrix(:,1);
  longitude = data_matrix(:,2);
  height_gps = data_matrix(:,3);
  height_bme = data_matrix(:,4);
  humidity_bme = data_matrix(:,5);
  temperature_bme = data_matrix(:,6);
  temperature_therm = data_matrix(:,7);
  
  length(height_gps)
  
  
  f1 = figure(1);
  plot(matrix_index,height_gps);
  hold on
  plot(matrix_index,height_bme);
  hold off
  saveas(f1,'height_time.fig');

  f2 = figure(2);
  scatter(height_bme,humidity_bme);
  saveas(f2,'humidity_height.fig')

  f3 = figure(3);
  scatter(height_bme,temperature_bme);
  saveas(f3,'humidity_temperature.fig')

  C = (height_bme - min(height_bme) ) / (max(height_bme) - min(height_bme));
  f4 = figure(4);
  geoscatter(latitude,longitude,36,C); % geoscatter(lat,lon,area,color)




end
