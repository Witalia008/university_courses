# https://www.redmine.org/projects/redmine/wiki/HowTo_install_rmagick_gem_on_Windows
# OR: http://www.julesberman.info/rubyhome.htm

# http://elementy.ru/posters/fractals/how_to_draw
# http://elementy.ru/posters/fractals/Newton#n=3
# http://fractalworld.xaoc.ru/Newton_fractal

require 'RMagick'
include Magick

WIDTH = 800
HEIGHT = 600
LOWER = -1.5
UPPER = 1.5
K = 16
MAX = 10
MIN = 1e-6
$image = Image.new(WIDTH, HEIGHT)

COLOURS = ['black'] + %w(red yellow green blue magenta cyan brown orange) * ((K + 6) / 8)

def project(x, fr, to, fr_n, to_n)
  1.0*(x-fr)/(to-fr)*(to_n-fr_n)+fr_n
end

$colours = {}
def get_colour(pt)
  if pt.real.nan? or pt.imag.nan? or pt.abs > MAX
    return COLOURS[0]
  end
  x = pt.real.to_i
  y = pt.imag.to_i
  $colours[[x,y]] = COLOURS[$colours.size + 1] unless $colours.include? [x,y]
  $colours[[x,y]]
end

def func(z)
  z**4-1
end
def deriv(z)
  4*z**3
end

def fractal(l_x, l_y, u_x, u_y)
  (l_x...u_x).each do |x|
    (l_y...u_y).each do |y|
      z = Complex(
          project(x, 0, WIDTH, LOWER, UPPER),
          project(y, 0, HEIGHT, LOWER, UPPER)
      )
      n = 0
      while (func(z).abs > MIN) && (z.abs < MAX) && n < K
        z = z - func(z)/deriv(z)
        n += 1
      end

      $image.pixel_color(x, y, COLOURS[n % K])#n == K ? COLOURS[0] : get_colour(z))
    end
  end
end

threads = []
threads << Thread.new { fractal(0, 0, WIDTH/2, HEIGHT/2) }
threads << Thread.new { fractal(WIDTH/2, 0, WIDTH, HEIGHT/2) }
threads << Thread.new { fractal(0, HEIGHT/2, WIDTH/2, HEIGHT) }
threads << Thread.new { fractal(WIDTH/2, HEIGHT/2, WIDTH, HEIGHT) }
threads.each(&:join)

$image.write('fractal.png')