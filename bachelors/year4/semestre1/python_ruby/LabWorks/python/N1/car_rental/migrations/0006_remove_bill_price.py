# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
        ('car_rental', '0005_order_date_placed'),
    ]

    operations = [
        migrations.RemoveField(
            model_name='bill',
            name='price',
        ),
    ]
