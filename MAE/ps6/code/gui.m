classdef gui < matlab.apps.AppBase
    % GUI Class for creating a user interface to interact with PAM signals
    % This class defines a graphical user interface (GUI) for manipulating
    % and visualizing Pulse Amplitude Modulation (PAM) signals. It allows
    % the user to adjust parameters such as symbol sequence length, symbol
    % period, oversampling value, amplitude, SNR, and pulse vector length.
    % The interface includes sliders, numeric input fields, and checkboxes 
    % for user interaction.

    properties (Constant)
        FIGURE_WIDTH = 750;
        FIGURE_HEIGHT = 650;
        LABEL_WIDTH = 200;
        INPUT_WIDTH = 200;
        START_Y = 475;
        VERTICAL_SPACING = 50;
        SLIDER_Y = 50;
        SLIDER_LABEL_Y = 85;
        SLIDER_WIDTH = 300;
    end

    properties (Access = public)
        ui_figure       matlab.ui.Figure
        ui_axes1        matlab.ui.control.UIAxes
        ui_axes2        matlab.ui.control.UIAxes
        input_N         matlab.ui.control.NumericEditField
        input_T         matlab.ui.control.NumericEditField
        input_Q         matlab.ui.control.NumericEditField
        input_A         matlab.ui.control.NumericEditField
        input_SNR       matlab.ui.control.NumericEditField
        input_Np        matlab.ui.control.NumericEditField
        slider_samples  matlab.ui.control.Slider
        checkbox_enable matlab.ui.control.CheckBox
        label_N         matlab.ui.control.Label
        label_T         matlab.ui.control.Label
        label_Q         matlab.ui.control.Label
        label_A         matlab.ui.control.Label
        label_SNR       matlab.ui.control.Label
        label_Np        matlab.ui.control.Label
        label_samples   matlab.ui.control.Label
        signal1         double
        signal2         double
    end

    methods (Access = private)
        function create_slider(app)
            % Creates the slider for selecting the number of samples
            app.label_samples = uilabel(app.ui_figure, "Text", "Samples:");
            app.label_samples.Position = [50, app.SLIDER_LABEL_Y, app.LABEL_WIDTH, 20];
            app.slider_samples = uislider(app.ui_figure);
            app.slider_samples.Position = [50, app.SLIDER_LABEL_Y - 20, app.FIGURE_WIDTH - 100, 3];
            app.slider_samples.ValueChangedFcn = @(src, event) app.update_slider();
        end

        function create_widgets(app)
            % Creates the input fields and labels for user interaction
            components = {
                {"label_N", "Symbol Sequence Length (N):", "input_N", 25}, ...
                {"label_T", "Symbol Period (T):", "input_T", 4}, ...
                {"label_Q", "Oversampling Value (Q):", "input_Q", 2}, ...
                {"label_A", "Amplitude (A):", "input_A", 5}, ...
                {"label_SNR", "SNR:", "input_SNR", 20}, ...
                {"label_Np", "Length of Pulse Vector (Np):", "input_Np", 3} ...
            };

            % Loop through each component to create corresponding labels and input fields
            for i = 1:length(components)
                label_name = components{i}{1};
                label_text = components{i}{2};
                input_name = components{i}{3};
                default_value = components{i}{4};

                y_position = app.START_Y - (i - 1) * app.VERTICAL_SPACING + 50;

                app.(label_name) = uilabel(app.ui_figure, "Text", label_text);
                app.(label_name).Position = [50, y_position + 15, app.LABEL_WIDTH, 20];
                app.(input_name) = uieditfield(app.ui_figure, 'numeric');
                app.(input_name).Position = [50, y_position - 15, app.INPUT_WIDTH, 30];
                app.(input_name).Value = default_value;
                app.(input_name).ValueChangedFcn = @(src, event) app.update_inputs();
            end

            % Checkbox to enable or disable identifying multiples of T
            app.checkbox_enable = uicheckbox(app.ui_figure, "Text", "Identify Multiples of T");
            app.checkbox_enable.Position = [50, app.START_Y - length(components) * app.VERTICAL_SPACING - 30, 200, 30];
            app.checkbox_enable.ValueChangedFcn = @(src, event) app.toggle_markers();

            % Create the slider for sample selection
            create_slider(app);
        end

        function create_plot_area(app)
            % Creates the plot areas for displaying signals
            plot_area_y = app.START_Y - 2 * app.VERTICAL_SPACING;
            
            app.ui_axes1 = uiaxes(app.ui_figure);
            app.ui_axes1.Position = [300, plot_area_y, 400, 200];
            app.ui_axes1.XLabel.String = "Samples";
            app.ui_axes1.YLabel.String = "Amplitude";
            title(app.ui_axes1, "PAM Signal");

            app.ui_axes2 = uiaxes(app.ui_figure);
            app.ui_axes2.Position = [300, plot_area_y - 250, 400, 200];
            app.ui_axes2.XLabel.String = "Samples";
            app.ui_axes2.YLabel.String = "Amplitude";
            title(app.ui_axes2, "Matched Filter");
        end

        function update_inputs(app)
            % Updates slider limits and signal based on input field values
            app.slider_samples.Limits = [0, app.input_N.Value * app.input_Q.Value * 2];
            app.slider_samples.Value = app.input_N.Value * app.input_Q.Value;
            app.update_signals();
        end

        function update_slider(app)
            % Updates the signals when the slider value changes
            app.update_signals();
        end

        function toggle_markers(app)
            % Toggles the markers for identifying multiples of T
            plot_signal(app.signal1, app.input_T.Value, app.checkbox_enable.Value, app.ui_axes1);
            plot_signal(app.signal2, app.input_T.Value, app.checkbox_enable.Value, app.ui_axes2);
        end

        function update_signals(app)
            % Updates the signals based on input field and slider values
            N = app.input_N.Value;
            T = app.input_T.Value;
            Q = app.input_Q.Value;
            A = app.input_A.Value;
            SNR = app.input_SNR.Value;
            Np = app.input_Np.Value;
            idxs = app.slider_samples.Value;

            [app.signal1, app.signal2] = get_signals(N, T, Q, A, SNR, Np, idxs);
            app.toggle_markers();
        end

        function create_app(app)
            % Creates the entire application window and UI components
            app.ui_figure = uifigure("Position", [100, 100, app.FIGURE_WIDTH, app.FIGURE_HEIGHT]);
            app.ui_figure.Name = "MAE 2024 - Marc Franquesa Monés - 22-11-2024";

            title_label = uilabel(app.ui_figure, "Text", "MAE 2024 - Marc Franquesa Monés - 22-11-2024");
            title_label.Position = [(app.FIGURE_WIDTH - 400) / 2, app.FIGURE_HEIGHT - 50, 400, 30];
            title_label.HorizontalAlignment = "center";
            title_label.FontSize = 16;
            title_label.FontWeight = "bold";

            create_widgets(app);
            create_plot_area(app);
            update_inputs(app);
        end
    end

    methods (Access = public)
        function app = gui
            % Constructor for initializing the GUI app
            create_app(app);
        end
    end
end
