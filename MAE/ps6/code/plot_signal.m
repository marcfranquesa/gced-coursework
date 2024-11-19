function plot_signal(signal, T, markers, axes_handle)
    %PLOT_SIGNAL Plot a signal with optional markers and axes handling.
    %   PLOT_SIGNAL(SIGNAL, T, MARKERS, AXES_HANDLE) generates a stem plot
    %   of the signal with optional markers for the samples at multiples of
    %   the symbol period T. The plot can be customized with a specified 
    %   axes handle.
    %
    %   Inputs:
    %       SIGNAL     - The signal to plot (vector).
    %       T          - Symbol period (integer).
    %       MARKERS    - (Optional) Boolean indicating whether to add red 
    %                    markers at multiples of T (default is true).
    %       AXES_HANDLE - (Optional) Handle of the axes to plot on. If not 
    %                     provided, a new figure and axes are created.
    %
    %   Outputs:
    %       None. The function generates a stem plot with optional markers.
    
    idxs = 1:numel(signal);
    multiples_x = find(mod(idxs, T) == 0);
    multiples_y = signal(multiples_x);

    if nargin < 3
        markers = true;
    end

    if nargin < 4
        figure;
        axes_handle = axes;
    end

    stem(axes_handle, idxs, signal, "Color", "#0072BD");
    hold(axes_handle, "on");

    if markers
        plot(axes_handle, multiples_x, multiples_y, "o", "MarkerFaceColor", "#7E2F8E");
    end

    hold(axes_handle, "off");
    
    xlabel(axes_handle, "Samples");
    ylabel(axes_handle, "Amplitude");
end
