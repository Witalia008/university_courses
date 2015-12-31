# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
        ('car_rental', '0002_auto_20151021_1238'),
    ]

    operations = [
        migrations.AddField(
            model_name='order',
            name='returned',
            field=models.BooleanField(default=False),
        ),
    ]
