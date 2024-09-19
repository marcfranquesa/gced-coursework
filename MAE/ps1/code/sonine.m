ALPHA = 1.5;
N = 10;


sonine_pol = @(n)(sonine_pol_aux(n, ALPHA));

% LOOPING THROUGH ALL THE POLS
x = 0:0.1:8;
for i = 0:N
    p = sonine_pol(i);
    fprintf('S%d: ', i); disp(p);
    y = polyval(p, x);
    plot(x, y, "DisplayName", "S_{" + string(i) + "}");
    hold on;
end

% VISUALS
legend(BackgroundAlpha=0);
xticks(0:2:8), yticks(-10:5:10);
title("Sonine polynomials ($\alpha =" + string(ALPHA) + "$) up to degree " + string(N), "interpreter", "latex")
axis([0 8 -10 10]), grid on;
ax = gca;
ax.GridLineStyle = ':';
ax.GridColor = 0 * ones(1, 3);

function [p] = sonine_pol_aux(n, alpha)
    DP = {};
    DP{1} = 1;
    DP{2} = [-1 1 + alpha];
    
    for i=3:(n+1)
        p1 = conv([-1 2 * (i - 1) - 1 + alpha], DP{i-1});
        p2 = conv(((i - 1) - 1 + alpha ), DP{i-2});
        DP{i} = (p1 - [zeros(1, size(p1, 2) - size(p2, 2)) p2]) / (i - 1);
    end

    p = DP{n + 1};
end