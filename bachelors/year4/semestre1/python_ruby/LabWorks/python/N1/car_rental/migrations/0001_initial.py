# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations
from django.conf import settings


class Migration(migrations.Migration):

    dependencies = [
        migrations.swappable_dependency(settings.AUTH_USER_MODEL),
    ]

    operations = [
        migrations.CreateModel(
            name='Bill',
            fields=[
                ('id', models.AutoField(verbose_name='ID', primary_key=True, serialize=False, auto_created=True)),
                ('price', models.IntegerField()),
                ('add_price', models.IntegerField(default=0)),
                ('add_price_reason', models.TextField()),
            ],
        ),
        migrations.CreateModel(
            name='Car',
            fields=[
                ('id', models.AutoField(verbose_name='ID', primary_key=True, serialize=False, auto_created=True)),
                ('car_name', models.CharField(max_length=200)),
                ('year', models.IntegerField()),
                ('seat_number', models.IntegerField()),
                ('is_rented', models.BooleanField(default=False)),
            ],
        ),
        migrations.CreateModel(
            name='Order',
            fields=[
                ('id', models.AutoField(verbose_name='ID', primary_key=True, serialize=False, auto_created=True)),
                ('passport_number', models.CharField(max_length=10)),
                ('term', models.IntegerField()),
                ('was_paid', models.BooleanField(default=False)),
                ('accepted', models.BooleanField()),
                ('rej_reason', models.TextField()),
                ('car', models.ForeignKey(to='car_rental.Car')),
                ('customer', models.ForeignKey(to=settings.AUTH_USER_MODEL)),
            ],
        ),
        migrations.AddField(
            model_name='bill',
            name='order',
            field=models.ForeignKey(to='car_rental.Order'),
        ),
    ]
