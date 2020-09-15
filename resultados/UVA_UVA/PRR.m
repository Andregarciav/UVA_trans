prr_dist = [92 90.9 92 92.1 91.8
        91 85 85 89 90
        85 84 84 85 84
        45 53 31 32 34
        55 59 57 56 58];
prr  = ones (1,5);
distancia = [0.1 0.2 0.4 0.6 0.8];

for i = 1:5
    prr(i) = mean(prr_dist(i,:));
end

figure(1)
    hold on
    title('PRR UVA-UVA LEDs', 'Fontsize', 13)
    plot(distancia,prr/100,'-s','LineWidth',3)
    ylim([0 1])
    xlim([0 1])
    xlabel('Distance (m)')%,'Fontsize', 30, 'LineWidth',5,'fontweight','bold')
    ylabel('PRR')%,'Fontsize', 30, 'LineWidth',5,'fontweight','bold')
    ax = gca;
    ax.XAxis.LineWidth = 3;
    ax.YAxis.LineWidth = 3;
    ax.XAxis.FontWeight = 'bold';
    ax.YAxis.FontWeight = 'bold';
    ax.XAxis.FontSize = 13;
    ax.YAxis.FontSize = 13;
    %saveas(gcf,'uva_uva_trans', 'svg')
    hold off


dR = [14.7 14.5 14.7 14.7 14.7
    14.6 13 12.9 14.1 14.3
    13 12.8 12.9 12.8 12.7
    4.31 5.27 3 3.16 3.39
    5.73 6.28 5.96 5 5];
data_rate  = ones (1,5);

for i = 1:5
    data_rate(i) = mean(dR(i,:));
end

figure(2)
    hold on
    title('Data Rate', 'Fontsize', 13)
    plot(distancia,data_rate,'-s','LineWidth',3)
    ylim([0 15])
    xlim([0 1])
    xlabel('Distance (m)')%,'Fontsize', 30, 'LineWidth',5,'fontweight','bold')
    ylabel('Data Rate (Kbps)')%,'Fontsize', 30, 'LineWidth',5,'fontweight','bold')
    ax = gca;
    ax.XAxis.LineWidth = 3;
    ax.YAxis.LineWidth = 3;
    ax.XAxis.FontWeight = 'bold';
    ax.YAxis.FontWeight = 'bold';
    ax.XAxis.FontSize = 13;
    ax.YAxis.FontSize = 13;
    saveas(gcf,'uva_uva_dataRate', 'svg')
hold off