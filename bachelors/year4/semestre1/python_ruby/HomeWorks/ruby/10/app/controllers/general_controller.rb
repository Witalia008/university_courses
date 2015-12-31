require 'spreadsheet'

FILEPATH = File.join(Rails.root, 'public', 'file.xls')
TMPFILE = File.join(Rails.root, 'public', 'file_tmp.xls')
PASSWORD = 'pass'

class GeneralController < ApplicationController
  before_filter :assign_vars

  def assign_vars
    @cols = 100
    @rows = 100
  end

  def index
  end

  def open
    if params[:password] == PASSWORD
      @pass = params[:password]
      Spreadsheet.open FILEPATH do |file|
        @sheet = file.worksheet 0
      end
    else
      render 'index'
    end
  end

  def update
    if params[:password] == PASSWORD
      Spreadsheet.open FILEPATH do |file|
        @sheet = file.worksheet 0

        params.each do |key, val|
          if key.include? ','
            row, col = key.split(',').map(&:to_i)
            print(row, col, val)
            @sheet[row,col] = val
          end
        end
        file.write TMPFILE
      end
      FileUtils.cp(TMPFILE, FILEPATH)
      FileUtils.rm_f(TMPFILE)
      render 'open'
    else
      render 'index'
    end
  end

  def close
    @file.close
  end
end
