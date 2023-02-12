import tkinter
import customtkinter
import tkinter.messagebox
import numpy as np

##########################
# Evan Peck
# Capstone Project
# 2/11/23
# Group 6, Skittlz Dynasty
# GUI for control of Generant Compaction Station
##########################

###### NOTES ########
# Adjust to actual pixel size of mini PC monitor----Set pixel size
# Adjust Cam Amplitude frame----DONE
# Adjust slider to be uniform length
# Reduce width of entry boxes
# Connect entry box value with slider value----DONE
# Set slider bar limits and increments----DONE
# Save values as variables
# Add AutoLiv and UofU images
# Get feedback on color pallet?
# Initialize entry values when activated----DONE (workaround I think, idk I forgot)
# Add opening window w/ images, manual/automatic

customtkinter.set_appearance_mode("Dark")
customtkinter.set_default_color_theme("blue")

freqBounds1 = [50, 100]
freqBounds06 = [50, 125]
freqBounds04 = [50, 150]
freqBoundsCustom = [50, 150]
freqBounds = [freqBounds1[0], freqBounds1[1]]


class App(customtkinter.CTk):
    def __init__(self):
        super().__init__()

        self.title("AutoLiv Generant Compaction Station Control")
        self.geometry(f"{1366}x{768}")

        # Grid Layout
        self.grid_columnconfigure(1, weight=1)
        self.grid_columnconfigure((2, 3, 4, 5, 6), weight=1)
        self.grid_rowconfigure((0, 1, 2, 3, 4, 5), weight=1)

        # Radiobuttons
        self.radiobutton_frame = customtkinter.CTkFrame(self)
        self.radiobutton_frame.grid(row=0, column=0, rowspan=1, columnspan=1, padx=(20, 0), pady=(20, 0), sticky="nsew")
        self.radio_var = tkinter.IntVar(value=0)
        self.label_radio_group = customtkinter.CTkLabel(master=self.radiobutton_frame, text="Cam Amplitude")
        self.label_radio_group.grid(row=0, column=1, columnspan=2, padx=10, pady=(20, 20), sticky="ew")
        self.amp_1 = customtkinter.CTkRadioButton(master=self.radiobutton_frame, text="1mm",
                                                  variable=self.radio_var, value=0, command=self.setBounds)
        self.amp_1.grid(row=1, column=0, padx=20, pady=10, sticky="n")
        self.amp_06 = customtkinter.CTkRadioButton(master=self.radiobutton_frame, text="0.6mm",
                                                   variable=self.radio_var, value=1, command=self.setBounds)
        self.amp_06.grid(row=1, column=1, padx=20, pady=10, sticky="n")
        self.amp_04 = customtkinter.CTkRadioButton(master=self.radiobutton_frame, text="0.4mm",
                                                   variable=self.radio_var, value=2, command=self.setBounds)
        self.amp_04.grid(row=1, column=2, padx=20, pady=10, sticky="n")
        self.amp_custom = customtkinter.CTkRadioButton(master=self.radiobutton_frame, text="Custom",
                                                   variable=self.radio_var, value=3, command=self.setBounds)
        self.amp_custom.grid(row=1, column=3, padx=20, pady=10, sticky="n")

        # Frequency Slider
        self.freq_frame = customtkinter.CTkFrame(self, fg_color="transparent")
        self.freq_frame.grid(row=1, column=0, padx=(10, 0), pady=(20, 0), sticky="nsew")
        self.freq_frame.grid_columnconfigure(1, weight=1)
        self.freq_frame.grid_rowconfigure(2, weight=1)
        self.freq_var = "disabled"
        self.freqSlider = customtkinter.CTkSlider(self.freq_frame, orientation="horizontal", state="disabled",
                                                  number_of_steps=250, from_=freqBounds[0], to=freqBounds[1])
        self.freqSlider.bind("<ButtonRelease-1>", self.checkFreqSlider)
        self.freqSlider.grid(row=1, column=1, columnspan=2, padx=(10, 10), pady=(10, 10), sticky="ew")

        self.vibButton = customtkinter.CTkCheckBox(self.freq_frame, text="Enable\nVibration",
                                                   command=self.freqToggle, onvalue=1, offvalue=0)
        self.vibButton.grid(row=1, column=0, padx=(10, 10), pady=(10, 10))

        self.freqEntry = customtkinter.CTkEntry(self.freq_frame, placeholder_text="Hz", state="disabled",
                                                validate='focusout', validatecommand=self.checkFreqEntry, width=25)
        self.freqEntry.grid(row=1, column=3, padx=(10, 10), pady=(10, 10), sticky='w')

        self.freqLabel = customtkinter.CTkLabel(self.freq_frame, text="Hz   ")
        self.freqLabel.grid(row=1, column=4, padx=(0, 0), pady=(10, 10), sticky='w')

        # Force Slider
        self.force_frame = customtkinter.CTkFrame(self, fg_color="transparent")
        self.force_frame.grid(row=2, column=0, padx=(10, 0), pady=(20, 0), sticky="nsew")
        self.force_frame.grid_columnconfigure(1, weight=1)
        self.force_frame.grid_rowconfigure(3, weight=1)
        self.force_var = "disabled"
        self.forceSlider = customtkinter.CTkSlider(self.force_frame, orientation="horizontal", state="disabled",
                                                   number_of_steps=250, from_=0, to=500)
        self.forceSlider.grid(row=2, column=1, columnspan=2, padx=(10, 10), pady=(10, 10), sticky="ew")

        self.compactButton = customtkinter.CTkCheckBox(self.force_frame, text="Enable\nCompaction",
                                                       command=self.forceToggle, onvalue=1, offvalue=0)
        self.compactButton.grid(row=2, column=0, padx=(10, 10), pady=(10, 10))

        self.forceEntry = customtkinter.CTkEntry(self.force_frame, placeholder_text="N", state="disabled", width=25)
        self.forceEntry.grid(row=2, column=3, padx=(10, 10), pady=(10, 10), sticky='w')

        self.forceLabel = customtkinter.CTkLabel(self.force_frame, text="N    ")
        self.forceLabel.grid(row=2, column=4, padx=(0, 0), pady=(10, 10), sticky='e')

        # Rotation Slider
        self.rotate_frame = customtkinter.CTkFrame(self, fg_color="transparent")
        self.rotate_frame.grid(row=3, column=0, padx=(10, 0), pady=(20, 0), sticky="nsew")
        self.rotate_frame.grid_columnconfigure(1, weight=1)
        self.rotate_frame.grid_rowconfigure(4, weight=1)
        self.rotate_var = "disabled"
        self.rotateSlider = customtkinter.CTkSlider(self.rotate_frame, orientation="horizontal", state="disabled",
                                                    number_of_steps=250, from_=0, to=50)
        self.rotateSlider.grid(row=3, column=1, columnspan=2, padx=(10, 10), pady=(10, 10), sticky="ew")

        self.rotateButton = customtkinter.CTkCheckBox(self.rotate_frame, text="Enable\nRotation",
                                                      command=self.rotateToggle, onvalue=1, offvalue=0)
        self.rotateButton.grid(row=3, column=0, padx=(10, 10), pady=(10, 10))

        self.rotateEntry = customtkinter.CTkEntry(self.rotate_frame, placeholder_text="rad/s", state="disabled", width=25)
        self.rotateEntry.grid(row=3, column=3, padx=(10, 10), pady=(10, 10), sticky='w')

        self.rotateLabel = customtkinter.CTkLabel(self.rotate_frame, text="rad/s")
        self.rotateLabel.grid(row=3, column=4, padx=(0, 0), pady=(10, 10), sticky='e')

        # Run Time
        self.time_frame = customtkinter.CTkFrame(self, fg_color="transparent")
        self.time_frame.grid(row=4, column=0, padx=(10, 0), pady=(20, 0), sticky="nsew")
        self.time_frame.grid_columnconfigure(1, weight=1)
        self.time_frame.grid_rowconfigure(5, weight=1)
        self.time_var = "disabled"
        self.timeSlider = customtkinter.CTkSlider(self.time_frame, orientation="horizontal", state="disabled",
                                                  number_of_steps=250, from_=0, to=20)
        self.timeSlider.grid(row=4, column=1, columnspan=2, padx=(10, 10), pady=(10, 10), sticky="ew")

        self.timeButton = customtkinter.CTkCheckBox(self.time_frame, text="Enable\nRun Time", command=self.timeToggle,
                                                    onvalue=1, offvalue=0)
        self.timeButton.grid(row=4, column=0, padx=(10, 10), pady=(10, 10))

        self.timeEntry = customtkinter.CTkEntry(self.time_frame, placeholder_text="sec.", state="disabled", width=25)
        self.timeEntry.grid(row=4, column=3, padx=(10, 10), pady=(10, 10), sticky='w')

        self.timeLabel = customtkinter.CTkLabel(self.time_frame, text="sec. ")
        self.timeLabel.grid(row=4, column=4, padx=(0, 0), pady=(10, 10), sticky='e')

        # Current Placeholder
        self.results_frame = customtkinter.CTkFrame(self)
        self.results_frame.grid(row=0, column=1, rowspan=5, columnspan=3, padx=(20, 0), pady=(20, 0), sticky="nsew")
        self.results_var = tkinter.IntVar(value=0)
        self.results_label = customtkinter.CTkLabel(master=self.results_frame, text="Results")
        self.results_label.grid(row=0, column=1, padx=10, pady=(20, 20))

    # Functions to set bounds due to amplitude
    def setBounds(self):
        global freqBounds
        radio_var = self.radio_var.get()
        if radio_var == 0:
            freqBounds = [freqBounds1[0], freqBounds1[1]]
        elif radio_var == 1:
            freqBounds = [freqBounds06[0], freqBounds06[1]]
        elif radio_var == 2:
            freqBounds = [freqBounds04[0], freqBounds04[1]]
        elif radio_var == 3:
            freqBounds = [freqBoundsCustom[0], freqBoundsCustom[1]]
            print("Custom cam amplitude selected\n*Make changes to allow for amplitude entry*")
        else:
            print('Something wrong with RadioButton function setBounds')
        self.freqSlider.configure(number_of_steps=250, from_=freqBounds[0], to=freqBounds[1])
        print('freqBounds:[' + str(freqBounds[0]) + ', ' + str(freqBounds[1]) + ']')

    # Functions to disable sliders and entry boxes when related function is not enabled by the user

    def freqToggle(self):

        if self.vibButton.get() == 1:
            self.freqSlider.configure(state="normal")
            self.freqEntry.configure(state="normal")
        else:
            self.freqSlider.configure(state="disabled")
            self.freqEntry.delete(0, len(self.freqEntry.get()))
            self.freqEntry.configure(state="disabled")

    def forceToggle(self):
        if self.compactButton.get() == 1:
            self.forceSlider.configure(state="normal")
            self.forceEntry.configure(state="normal")
        else:
            self.forceSlider.configure(state="disabled")
            self.forceEntry.delete(0, len(self.forceEntry.get()))
            self.forceEntry.configure(state="disabled")

    def rotateToggle(self):
        if self.rotateButton.get() == 1:
            self.rotateSlider.configure(state="normal")
            self.rotateEntry.configure(state="normal")
        else:
            self.rotateSlider.configure(state="disabled")
            self.rotateEntry.delete(0, len(self.rotateEntry.get()))
            self.rotateEntry.configure(state="disabled")

    def timeToggle(self):
        if self.timeButton.get() == 1:
            self.timeSlider.configure(state="normal")
            self.timeEntry.configure(state="normal")
        else:
            self.timeSlider.configure(state="disabled")
            self.timeEntry.delete(0, len(self.timeEntry.get()))
            self.timeEntry.configure(state="disable")

    # Functions to sync slider and entry values

    def checkFreqEntry(self):
        try:                                            #Check if entry is numeric (int or float)
            val = int(self.freqEntry.get())
            val1 = True
        except ValueError:
            try:
                val = float(self.freqEntry.get())
                val1 = True
            except ValueError:
                val1 = False

        if val1 == True:                                    #If entry is numeric, set slider to entry value
            if freqBounds[0] <= val <= freqBounds[1]:
                self.freqSlider.set(val)
                return True
        else:                                                       #If entry is not numeric or out of freqBounds, print an error with the proper bounds
            self.freqEntry.delete(0, len(self.freqEntry.get()))
            print('Invalid frequency')
            print('Enter a value between ' + str(freqBounds[0]) + ' and ' + str(freqBounds[1]) + 'Hz')
            return False

    def checkFreqSlider(self, second):                              #When the freqSlider is changed, update the freqEntry box to match
        if isinstance(self.freqEntry.get(), int):
            if self.freqSlider.get() != int(self.freqEntry.get()):
                self.freqEntry.delete(0, len(self.freqEntry.get()))
                self.freqEntry.insert(self.freqSlider.get)
                return True
        else:
            self.freqEntry.delete(0, len(self.freqEntry.get()))
            self.freqEntry.insert(0, round(self.freqSlider.get(), 1))
            return True


if __name__ == "__main__":
    app = App()
    app.mainloop()
