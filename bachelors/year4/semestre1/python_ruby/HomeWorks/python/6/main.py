import random
import tkinter as tk
import re

CONTROL = 0x0004
ALT = 0x0008


class Application(tk.Frame):
    def __init__(self, master=None):
        tk.Frame.__init__(self, master)
        self.pack()
        self.createWidgets()

        self.tags = []
        self.segms = []
        self.lines = []

    def createWidgets(self):
        tk.Label(self, text='Your regex:').grid(row=0, column=0, columnspan=2)

        self.regex_field = tk.Entry(self)
        self.regex_field.grid(row=1, column=0, columnspan=2, sticky='nsew', padx=2, pady=2)

        self.check_box_panel = tk.Frame(self)
        self.ignorecase = tk.BooleanVar()
        tk.Checkbutton(self.check_box_panel, text='Ignore case?',
                       variable=self.ignorecase, command=self.recalc)\
                .pack(side='top')
        self.check_box_panel.grid(row=2, column=0, columnspan=2, sticky='nsew', padx=2, pady=2)

        self.text_field = tk.Text(self, borderwidth=3)
        self.text_field.grid(row=3, column=0, sticky='nsew', padx=2, pady=2)

        scrollb = tk.Scrollbar(self, command=self.text_field.yview)
        scrollb.grid(row=3, column=1, sticky='nsew')
        self.text_field['yscrollcommand'] = scrollb.set

        self.master.bind('<Alt-r>', lambda e: self.regex_field.focus_set())
        self.master.bind('<Alt-R>', lambda e: self.regex_field.focus_set())
        self.master.bind('<Alt-t>', lambda e: self.text_field.focus_set())
        self.master.bind('<Alt-T>', lambda e: self.text_field.focus_set())
        self.master.bind('<Control-q>', lambda e: root.quit())
        self.master.bind('<Control-Q>', lambda e: root.quit())

        self.regex_field.bind('<KeyRelease>', lambda e: self.recalc())
        self.text_field.bind('<KeyRelease>', lambda e: self.recalc())

    def recalc(self):
        for (segm, tag) in zip(self.segms, self.tags):
            self.text_field.tag_remove(tag, self.get_rowcol(segm[0]), self.get_rowcol(segm[1]))

        self.lines = self.text_field.get(1.0, tk.END).split('\n')
        # print(self.lines)
        self.segms = []
        self.tags = []
        self.tag_colours = []
        try:
            p = re.compile(self.regex_field.get(), flags=0 if not self.ignorecase.get() else re.IGNORECASE)
            for m in p.finditer(self.text_field.get(1.0, tk.END)):
                self.tags.append('tag%d' % len(self.segms))
                self.segms.append((m.start(), m.start() + len(m.group())))
                self.tag_colours.append(('red', 'black'))
        except:
            print('Wrong regexp')
        self.highlight()

    def highlight(self):
        for (segm, tag, colour) in zip(self.segms, self.tags, self.tag_colours):
            # print(segm, tag, colour)
            self.text_field.tag_add(tag, self.get_rowcol(segm[0]), self.get_rowcol(segm[1]))
            self.text_field.tag_config(tag, background=colour[0], foreground=colour[1])

    def get_rowcol(self, index):
        # print(self.lines)
        # print(index)
        pos = 0
        while index >= len(self.lines[pos])+1:
            index -= len(self.lines[pos])+1
            pos += 1
        # print(pos+1, index+1)
        return '%d.%d' % (pos+1, index)


root = tk.Tk()
app = Application(master=root)
app.mainloop()
